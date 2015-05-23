#include "shell.h"

#include <signal.h>
#include <sys/types.h>

static pid_t CURRENT_PID = 0;

static void signal_handler(int signum) {
  switch(signum) {
    case SIGINT: {
      if(CURRENT_PID != 0) {
        kill(CURRENT_PID, SIGINT);
      }

      CURRENT_PID = 0;
      break;
    }
  }
}

void shell_register_current_pid(pid_t pid) {
  CURRENT_PID = pid;
}

void shell_register_signals() {
  signal(SIGINT, signal_handler);
}
