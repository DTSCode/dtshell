#include "shell.h"

#include <errno.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

static char **split(char *line, int *arg_count, char *delim) {
  char *copy = malloc(strlen(line));

  strcpy(copy, line);

  char **words = NULL;
  char *word = strtok(copy, delim);
  size_t counter = 0;

  while(word != NULL) {
    words = (char**)realloc(words, (counter+1)*sizeof(char*));
    words[counter] = (char*)malloc(strlen(word)+1);
    strcpy(words[counter], word);
    counter++;
    word = strtok(NULL, delim);
  }

  words = (char**)realloc(words, (counter+1)*sizeof(char*));
  words[counter] = NULL;
  *arg_count = counter;
  free(copy);
  return words;
}

static bool dir_exists(char path[]) {
    struct stat sb;
    bool exists = false;

    if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        exists = true;
    }

    return exists;
}

static bool run_builtin(char **args, int arg_count) {
  bool is_builtin_command = false;

  if(strcmp(args[0], "cd") == 0) {
    if((arg_count > 1 && strcmp(args[1], "~") == 0) || arg_count == 1) {
      chdir(getenv("HOME"));
    }

    else {
      if(dir_exists(args[1])) {
        chdir(args[1]);
      }

      else {
        fprintf(stderr, "dtsh: %s: directory does not exist\n", args[1]);
      }
    }

    is_builtin_command = true;
  }

  else if(strcmp(args[0], "exit") == 0) {
    exit(1);
  }

  return is_builtin_command;
}

static char **redirect(char **args, int arg_count) {
  if(strcmp(args[arg_count-2], ">") == 0) {
    int fd = open(args[arg_count-1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    dup2(fd, fileno(stdout));
    args[arg_count-2] = 0;
    args[arg_count-1] = 0;
  }

  else if(strcmp(args[arg_count-2], ">>") == 0) {
    int fd = open(args[arg_count-1], O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    dup2(fd, fileno(stdout));
    args[arg_count-2] = 0;
    args[arg_count-1] = 0;
  }

  else if(strcmp(args[arg_count-2], "<") == 0) {
    int fd = open(args[arg_count-1], O_RDONLY);
    dup2(fd, fileno(stdin));
    args[arg_count-2] = 0;
    args[arg_count-1] = 0;
  }

  return args;
}

static void execute(char *line) {
  int arg_count;
  char **args = split(line, &arg_count, " ");

    if(!run_builtin(args, arg_count)) {
      pid_t pid = fork();

      if(pid == 0) {
        if(arg_count >= 3) {
          args = redirect(args, arg_count);
        }

        shell_register_current_pid(pid);
        execvp(args[0], args);
        fprintf(stderr, "error: couldn't execute %s\n", args[0]);
      }

      else {
        int status;
        wait(&status);
      }
    }
}

void shell_execute(char *line) {
  int arg_count;
  char **args = split(line, &arg_count, " ");
  execute(line);
  free(args);
}
