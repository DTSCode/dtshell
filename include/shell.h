#ifndef _ROOT_DTSH_SHELL_H__
#define _ROOT_DTSH_SHELL_H__

#include <sys/types.h>
#include <stdbool.h>

void shell_register_current_pid(pid_t pid);
void shell_register_signals();
char *shell_getline(char*, char*);
void shell_execute(char*);

#endif
