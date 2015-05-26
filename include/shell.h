#ifndef _ROOT_DTSH_SHELL_H__
#define _ROOT_DTSH_SHELL_H__

/*
 * These defines remove warnings of implicit function declarations
*/

#define _POSIX_SOURCE
#define _GNU_SOURCE

/*
 * Common headers that I use in most source files
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

void shell_register_current_pid(pid_t pid);
void shell_register_signals();
char *shell_getline(char*, char*);
void shell_execute(char*);

#endif
