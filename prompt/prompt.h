#ifndef PROMPT_H_
#define PROMPT_H_

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define USER_COLOR ANSI_COLOR_CYAN
#define DIR_COLOR ANSI_COLOR_MAGENTA

/**
 * @brief this function print the prompt of the shell.
 the prompt consist of user name and host name and current workin directory.  
 * @return pointer to the prompt.
 */
char * printPrompet(void);
/**
 * @brief this function print the header of the shell at the beginning or
  when clear command executed.
 * 
 */
void printHeader(void);


#endif /* PROMPT_H_ */
