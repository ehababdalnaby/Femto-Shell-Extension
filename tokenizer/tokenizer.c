#include "tokenizer.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


void redirection(char **argv) {
  int i = 1;
  int endOfargv = -1;
  int oldfd = -1, newfd = -1;
  while (argv[i]) {
    if (strcmp(argv[i], ">") == 0) {
      oldfd = open(argv[i + 1], O_WRONLY | O_CREAT, 0644);
      if (oldfd != -1) {
        newfd = dup2(oldfd, 1);
        if (newfd == -1) {
          fprintf(stderr, "shell: %s: %s\n", argv[i + 1], strerror(errno));
          // perror(strerror(errno));
          exit(errno);
        }
      } else {
        fprintf(stderr, "shell: %s: %s\n", argv[i + 1], strerror(errno));
        exit(errno);
      }
      if (endOfargv == -1) {
        endOfargv = i;
      }
    } else if (strcmp(argv[i], "2>") == 0) {
      oldfd = open(argv[i + 1], O_WRONLY | O_CREAT, 0644);
      if (oldfd != -1) {
        newfd = dup2(oldfd, 2);
        if (newfd == -1) {
          fprintf(stderr, "shell: %s: %s\n", argv[i + 1], strerror(errno));
          exit(errno);
        }
      } else {
        fprintf(stderr, "shell: %s: %s\n", argv[i + 1], strerror(errno));
        exit(errno);
      }
      if (endOfargv == -1) {
        endOfargv = i;
      }
    } else if (strcmp(argv[i], "<") == 0) {
      oldfd = open(argv[i + 1], O_RDONLY);
      if (oldfd != -1) {
        newfd = dup2(oldfd, 0);
        if (newfd == -1) {
          fprintf(stderr, "shell: %s: %s\n", argv[i + 1], strerror(errno));
          exit(errno);
        }
      } else {
        fprintf(stderr, "shell: %s: %s\n", argv[i + 1], strerror(errno));
        exit(errno);
      }
      if (endOfargv == -1) {
        endOfargv = i;
      }
    }
    i++;
  }
  if (endOfargv != -1) {
    argv[endOfargv] = NULL;
  }
}

int tokenstr(char *buf, char del, char **argv) {
  int i = 0;
  int argv_index = 0;
  while (buf[i] != '\0') {
    if (buf[i] != del) {
      argv[argv_index] = &buf[i];
      while (buf[i] != del && buf[i] != '\0') {
        // printf("%c\n",buf[i]);
        i++;
      }
      buf[i] = '\0';
      i++;
      argv_index++;
    } else {
      i++;
    }
  }
  return argv_index;
}

void parseLine(char *line, char **argv) {
  char *token;
  int i = 0;
  i = tokenstr(line, ' ', argv);
  if (strcmp(argv[0], "ls") == 0) {
    static char color[] = "--color=auto";
    argv[i] = color;
    argv[i + 1] = NULL;
  } else {
    argv[i] = NULL;
  }
}