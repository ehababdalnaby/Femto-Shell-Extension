/**
 * @file vars.h
 * @author Ehab Omara
 * @brief contais the function that will responsable for local variables
 * and export local variables to env variables
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef VARS_H_
#define VARS_H_

/**
 * @brief the function search for a character in a string
 * 
 * @param str the string to search for the character in it
 * @param letter the letter that the function will search for it in the string 
 * @return int the index of the character in the string based on 0.
 * @retval -1 if the character doesn't exist
 */
int findChar(char *str, char letter);
/**
 * @brief check if the argumnts is a local variable or not
 * 
 * @param argv the argumnts that mau contains the local variable 
 * @return int the index of the equal sign '='
 * @retval 0 if it is not a variable 
 */
int isVariable(char **argv);
/**
 * @brief 
 * 
 * @param[in] var 
 * @param[out] firstEmptySpace 
 * @return int 
 */
int isVarExist(char *var, int *firstEmptySpace);
void setVariable(char **argv, int end_of_var_name);
void set(void);
void export(char **argv);


#endif /* VARS_H_ */
