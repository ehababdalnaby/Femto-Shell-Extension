#ifndef VARS_H_
#define VARS_H_

int findChar(char *str, char letter);
int isVariable(char **argv);
int isVarExist(char *var, int *firstEmptySpace);
void setVariable(char **argv, int end_of_var_name);
void set(void);
void export(char **argv);


#endif /* VARS_H_ */
