#include "builtinCMD.h"
#include <stdio.h>
#include <unistd.h>

extern char *home;
void cd(char **argv) {
  if (argv[1]) {
    if (chdir(argv[1]) != 0) {
      printf("shell: %s: %s: No such file or directory\n", argv[0], argv[1]);
    }
  } else {
    chdir(home);
  }
}