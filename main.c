
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <ncursesw/curses.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define USER_COLOR ANSI_COLOR_CYAN
#define DIR_COLOR ANSI_COLOR_MAGENTA

#define LOCAL_VARS_NUM 100

extern char **environ;
char *localVar[LOCAL_VARS_NUM] = {0};
char *localVarValues[LOCAL_VARS_NUM] = {0};

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
          fprintf(stderr, "shell: %s: %s\n", argv[i+1], strerror(errno));
          //perror(strerror(errno));
          exit(errno);
        }
      } else {
        fprintf(stderr, "shell: %s: %s\n", argv[i+1], strerror(errno));
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
          fprintf(stderr, "shell: %s: %s\n", argv[i+1], strerror(errno));
          exit(errno);
        }
      } else {
        fprintf(stderr, "shell: %s: %s\n", argv[i+1], strerror(errno));
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
          fprintf(stderr, "shell: %s: %s\n", argv[i+1], strerror(errno));
          exit(errno);
        }
      } else {
        fprintf(stderr, "shell: %s: %s\n", argv[i+1], strerror(errno));
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

void printPrompet(void) {
  char host[10] = {0};
  struct passwd *user = NULL;
  user = getpwuid(geteuid());
  gethostname(host, 10);
  char dir[PATH_MAX] = {0};
  printf(USER_COLOR "%s@%s" ANSI_COLOR_RESET ":" DIR_COLOR "%s" ANSI_COLOR_RESET
                    "$ ",
         user->pw_name, host, getcwd(dir, PATH_MAX));
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

void cd(char **argv) {
  if (argv[1]) {
    if (chdir(argv[1]) != 0) {
      printf("shell: %s: %s: No such file or directory\n", argv[0], argv[1]);
    }
  } else {
    chdir("/home/ehab");
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

int findChar(char *str, char letter) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == letter) {
      return i;
    }
    i++;
  }
  return -1;
}

int isVariable(char **argv) {
  int result = 0;
  if (argv[1] != NULL) {
    result = 0;
  } else {
    int end_of_var_name = findChar(argv[0], '=');
    if (end_of_var_name != strlen(argv[0]) - 1)
      result = end_of_var_name;
  }
  return result;
}

int isVarExist(char *var, int *firstEmptySpace) {
  int i = 0;
  int result = -1;
  while (i < LOCAL_VARS_NUM && localVar[i]) {
    if (strcmp(var, localVar[i]) == 0) {
      result = i;
    }
    i++;
  }
  if (firstEmptySpace != NULL) {

    if (i < LOCAL_VARS_NUM) {
      *firstEmptySpace = i;
    } else {
      *firstEmptySpace = -1;
    }
  }
  return result;
}
void setVariable(char **argv, int end_of_var_name) {
  int lenOfVal = strlen(argv[0]) - 1 - end_of_var_name;
  char *var = (char *)malloc(end_of_var_name + 1);
  strncpy(var, argv[0], end_of_var_name);
  int firstEmptySpace = 0;
  int indexOfVar = isVarExist(var, &firstEmptySpace);
  if (indexOfVar != -1) {
    free(localVarValues[indexOfVar]);
    localVarValues[indexOfVar] = (char *)calloc(1, lenOfVal);
    strncpy(localVarValues[indexOfVar], &argv[0][end_of_var_name + 1],
            lenOfVal);
  } else if (firstEmptySpace != -1) {
    localVarValues[firstEmptySpace] = (char *)calloc(1, lenOfVal);
    localVar[firstEmptySpace] = (char *)calloc(1, end_of_var_name + 1);
    strncpy(localVar[firstEmptySpace], var, end_of_var_name);
    strncpy(localVarValues[firstEmptySpace], &argv[0][end_of_var_name + 1],
            lenOfVal);
  } else {
    printf("there is no avaliable space for [%s]\n", argv[0]);
  }
  free(var);
}

void set(void) {
  for (int i = 0; i < LOCAL_VARS_NUM; i++) {
    if (localVar[i]) {
      printf("%s=%s\n", localVar[i], localVarValues[i]);
    }
  }
}

void export(char **argv) {
  if (argv[1] != NULL) {

    int varIndex = isVarExist(argv[1], NULL);
    if (varIndex != -1) {
      setenv(argv[1], localVarValues[varIndex], 1);
    }
  }
  else
  {
    int i = 0;
    while (environ[i])
    {
      printf("declare -x %s\n",environ[i]); i++;
    }
  }
}

void printHeader(void) {
  printf("\n\n\n\x1b[46m*************************** My simple "
         "shell ***************************\x1b[0m\n");
  printf("\x1b[46m* Author: Ehab Omara                        "
         "                          *\x1b[0m\n");
  printf("\x1b[46m* Version: 1.0                              "
         "                          *\x1b[0m\n");
  printf("\x1b[46m* Date: 5/10/2022                           "
         "                          *\x1b[0m\n");
  printf("\x1b[46m***************************************"
         "********************************\x1b[0m\n\n");
}

int main(void) {
  char *argv[64];
  size_t len = 0;
  ssize_t readed = 0;
  system("clear");
  printHeader();
  while (1) {
  char *line = NULL;
    printPrompet();
    readed = getline(&line, &len, stdin);
    line[readed - 1] = '\0';
    if (readed != 1) {

      parseLine(line, argv);
      int end_of_var_name = isVariable(argv);
      if (end_of_var_name > 0) {
       // printf("it is var\n");
        setVariable(argv, end_of_var_name);
      } else if (strcmp(argv[0], "set") == 0) {
        set();
      } else if (strcmp(argv[0], "export") == 0) {
        export(argv);
      } else if (strcmp(argv[0], "exit") == 0) {
        exit(0);
      } else if (strcmp(argv[0], "cd") == 0) {
        cd(argv);
      } else {
        execute(argv);
      }
    }
    if(strcmp(argv[0],"clear") == 0)
    {
      printHeader();
    }
    free(line);
  }
  return 0;
}
