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

int ispipe(char **argv) {
  int result = -1;
  int i = 0;
  while (argv[i]) {
    if (strcmp(argv[i], "|") == 0) {
      result = i;
      break;
    }
    i++;
  }
  return result;
}

void executePipe(char **argv, int pipeIndex)
{
  int fd[2];

  pipe(fd);

  pid_t pid = fork();

  if (pid == -1)
    exit(2);

  if (pid == 0) {
    argv[pipeIndex] = NULL;
    close(fd[0]);               
    dup2(fd[1], 1); 
    close(fd[1]); 
    
    execvp(argv[0], &argv[0]);
  }

  else {
    close(fd[1]);              
    dup2(fd[0], 0); 
    close(fd[0]);
    execvp(argv[pipeIndex + 1], &argv[pipeIndex+1]);
  }
}

  void execute(char **argv) {
  char mypath[] = "/mnt/e/Linux/simpleShell/builtinCommands";
  char pathenv[strlen(mypath) + 10];
  pid_t pid = 0;
  int status = 0;
  pid = fork();
  if (pid > 0) {
    wait(&status);
  } else if (pid == 0) {
    int pipeIndex = 0;
    redirection(argv);
    if ((pipeIndex = ispipe(argv)) != -1) {
      executePipe(argv,pipeIndex);
    } else {

      execvp(argv[0], argv);
      sprintf(pathenv, "%s/%s", mypath, argv[0]);
      execve(pathenv, argv, environ);
      fprintf(stderr, "%s: command not found\n", argv[0]);
      exit(errno);
    }
  } else {
    perror(strerror(errno));
  }
}