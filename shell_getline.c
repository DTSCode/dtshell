#include "shell.h"

#include <stdio.h>
#include <stdarg.h>

#include <readline/readline.h>
#include <readline/history.h>

/*
 * Need to fix strange bug where backspacing on first character erases whole prompt.
 * Temporary fix in place
*/

char *shell_getline(char *promptfmt, ...) {
  va_list arguments;
  va_start (arguments, promptfmt);

  while(*promptfmt) {
    if(*promptfmt == '%' && *++promptfmt == 's') {
        fprintf(stdout, "%s", va_arg(arguments, char *));
        fflush(stdout);
    }

    else {
      fputc(*promptfmt, stdout);
      fflush(stdout);
    }

    promptfmt++;
  }

  va_end(arguments);
  fflush(stdout);
  char *line = readline("$ ");

  if(line) {
    add_history(line);
  }

  return line;
}
