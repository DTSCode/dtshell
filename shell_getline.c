#include "shell.h"

#include <stdio.h>
#include <stdarg.h>

#include <readline/readline.h>
#include <readline/history.h>

char *shell_getline(char *promptfmt, ...) {
  va_list arguments;
  va_start (arguments, promptfmt);

  while(*promptfmt) {
    char current = *promptfmt;

    if(current == '%') {
      if(*++promptfmt == 's') {
        fprintf(stdout, "%s", va_arg(arguments, char *));
      }

      else {
        fputc(*promptfmt, stdout);
      }
    }

    else {
      fputc(*promptfmt, stdout);
    }

    promptfmt++;
  }

  va_end(arguments);
  fflush(stdout);
  char *line = readline("");

  if(line) {
    add_history(line);
  }

  return line;
}
