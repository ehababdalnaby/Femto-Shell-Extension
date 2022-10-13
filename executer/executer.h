#ifndef EXECUTER_H_
#define EXECUTER_H_
/**
 * @brief Check if the arguments contains pipe caharacter |
 * 
 * @param argv this is the arguments to search for pipe cpmmand |
 * @return int return the index of the pipe command | in the arguments
 */
int ispipe(char **argv);
/**
 * @brief execute the pipe command
 *
 * @param argv this is the arguments for the command that will be executed.
 * @param pipeIndex the index of the pipe command | in the arguments
 */
void executePipe(char **argv, int pipeIndex);
/**
 * @brief execute external and built in commands
 * 
 * @param argv this is the arguments for the command that will be executed.
 */
void execute(char **argv);

#endif /* EXECUTER_H_ */
