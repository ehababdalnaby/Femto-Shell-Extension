
#include "./prompt/prompt.h"
#include "./tokenizer/tokenizer.h"
#include "./variables/vars.h"
#include "./executer/executer.h"
#include "./builtincmd/builtinCMD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


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
