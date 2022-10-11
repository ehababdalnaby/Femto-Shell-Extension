#include "executer.h"
#include "../tokenizer/tokenizer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;
void execute(char **argv) {
  char mypath[] = "/mnt/e/Linux/simpleShell/builtinCommands";
  char pathenv[strlen(mypath) + 10];
  pid_t pid = 0;
  int status = 0;
  pid = fork();
  if (pid > 0) {
    wait(&status);
  } else if (pid == 0) {
    redirection(argv);
    execvp(argv[0], argv);
    sprintf(pathenv, "%s/%s", mypath, argv[0]);
    execve(pathenv, argv, environ);
    fprintf(stderr, "%s: command not found\n", argv[0]);
    exit(errno);
  } else {
    perror(strerror(errno));
  }
}