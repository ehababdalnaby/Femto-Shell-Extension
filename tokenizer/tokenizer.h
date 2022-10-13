/**
 * @file tokenizer.h
 * @author Ehab Omara
 * @brief contains the function that will tokenize the line into arguments.
 * @version 0.1
 * @date 2022-10-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_


/**
 * @brief this function checkif there is a redirection in the arguments 
 and made the redirection if there is one in the arguments.
 * 
 * @param argv the arguments that will be passed to the command.
 */
void redirection(char **argv);
/**
 * @brief this function split the line entered into tokens.
 * 
 * @param buf this buffer contains the string that will be tokenized
 * @param del the character that is located between the arguments
 * @param argv array of pointers that every pointer will point to one of the tokens
 * @return 
 * @retval int returns the number of tokens or arguments.
 */
int tokenstr(char *buf, char del, char **argv);
/**
 * @brief this function is just a wrapper for #tokenstr function
 * 
 * @param line the input line entered by the user
 * @param argv array of pointers that every pointer will point to one of the tokens
 */
void parseLine(char *line, char **argv);

#endif /* TOKENIZER_H_ */
