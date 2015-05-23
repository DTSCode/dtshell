/*
 * Todo:
 *  Make shell hot-swappable via dlfcn.h
 *  Need to put more work into signal handling
 *  Put in piping
 *  Fix readline bug
*/

#include "shell.h"

#include <stdbool.h>
#include <string.h>

#include <unistd.h>

int main(int argc, char **argv, char **env) {
  shell_register_signals();

  while(true) {
    shell_register_signals();
    char hostname[7];
    gethostname(hostname, 7);
    char *line = shell_getline("%s@dtsh: %s", hostname, getcwd(NULL, 0));

    if(strcmp(line, "") == 0) {
      continue;
    }

    shell_execute(line);
  }
}
