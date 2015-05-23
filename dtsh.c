/*
 * Todo:
 *  Make shell hot-swappable via dlfcn.h
 *  Put in piping
*/

#include "shell.h"

#include <stdbool.h>
#include <string.h>

#include <unistd.h>

int main(int argc, char **argv, char **env) {
  shell_register_signals();

  while(true) {
    char hostname[7];
    gethostname(hostname, 7);
    char *line = shell_getline("%s@dtsh: %s$ ", hostname, getcwd(NULL, 0));

    if(strcmp(line, "") == 0) {
      continue;
    }

    shell_execute(line);
  }
}
