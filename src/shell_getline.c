#include "shell.h"

#include <pwd.h>

#include <readline/readline.h>
#include <readline/history.h>

static char *getuser() {
  uid_t uid = geteuid ();
  struct passwd *pw = getpwuid(uid);

  if(pw) {
    return pw->pw_name;
  }

  return "";
}


static int append(char **str, const char *buf, int size) {
  char *nstr;

  if(*str == NULL) {
    nstr = malloc(size + 1);
    memcpy(nstr, buf, size);
    nstr[size] = '\0';
  }

  else {
    if(asprintf(&nstr, "%s%.*s", *str, size, buf) == -1) {
      return -1;
    }

    free(*str);
  }

  *str = nstr;
  return 0;
} 

static char *build_prompt(char *fmt, char *prompt) {
  prompt = NULL; /* Zero out all data in prompt */

  while(*fmt) {
    if(*fmt == '%') {
      switch(*++fmt) {
        case 'u': {
          char *user = getuser();
          append(&prompt, user, strlen(user));
          break;
        }

        case 'd': {
          char *pwd = getcwd(NULL, 0);
          append(&prompt, pwd, strlen(pwd));
          break;
        }

        default: {
          append(&prompt, &*fmt, 1);
        }
      }
    }

    else {
      append(&prompt, &*fmt, 1);
    }

    fmt++;
  }

  return prompt;
}

char *shell_getline(char *promptfmt, char *line) {
  char *prompt = NULL;
  prompt = build_prompt(promptfmt, prompt); /* expand promptfmt into an actual meaningful prompt (such as dtscode@dtsh: /home/dtscode/$) */
  line = readline(prompt);

  while(strcmp(line, "") == 0) {
    line = readline(prompt);
  }

  free(prompt);
  add_history(line);
  return line;
}
