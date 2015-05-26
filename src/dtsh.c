#include "shell.h"

int main(int argc, char **argv) {
  shell_register_signals(); /* Hook SIGINT (namely ctrl-c) */

  while(true) {
    char *line = shell_getline("%u@dtsh: %d$ ", line);
    shell_execute(line);
    free(line);
  }
}
