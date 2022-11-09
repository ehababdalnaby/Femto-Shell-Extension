#include "prompt.h"
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT_SIZE 100
char *home = NULL;
//static char prompt[PROMPT_SIZE] = {0};


char *printPrompet(void) {
       static char *prompt = NULL;
       prompt = (char*)calloc(1,100);
  char host[10] = {0};
  struct passwd *user = NULL;
  user = getpwuid(geteuid());
  home = user->pw_dir;
  gethostname(host, 10);
  char dir[PATH_MAX] = {0};
  prompt = realloc(prompt,PATH_MAX+strlen(user->pw_name)+strlen(host)+1);
  sprintf(prompt,
          USER_COLOR "%s@%s" ANSI_COLOR_RESET ":" DIR_COLOR
                     "%s" ANSI_COLOR_RESET"$ ",
          user->pw_name, host, getcwd(dir, PATH_MAX));
          return prompt;
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
