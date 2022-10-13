#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vars.h"

/**
 * @brief size of the local variables array
 * 
 */
#define LOCAL_VARS_NUM 100
/**
 * @brief this array contains the env variables   
 * 
 */
extern char **environ;
/**
 * @brief array that contains the local variables names
 * 
 */
char *localVar[LOCAL_VARS_NUM] = {0};
/**
 * @brief array that contains the local variables values
 * 
 */
char *localVarValues[LOCAL_VARS_NUM] = {0};




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
  } else {
    int i = 0;
    while (environ[i]) {
      printf("declare -x %s\n", environ[i]);
      i++;
    }
  }
}