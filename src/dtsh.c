/*
 * Todo:
 *  Make shell hot-swappable via dlfcn.h
 *  Need to put more work into signal handling
 *  Put in piping
 *  Fix readline bug
*/

#include "shell.h"

#include <string.h>

#include <unistd.h>

int main(int argc, char **argv, char **env) {
  shell_register_signals();

  while(true) {
    char *line = shell_getline("%u@dtsh: %d$ ", line);
    shell_execute(line);
  }
}
