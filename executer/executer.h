#ifndef EXECUTER_H_
#define EXECUTER_H_

int ispipe(char **argv);
void executePipe(char **argv, int pipeIndex);
void execute(char **argv);

#endif /* EXECUTER_H_ */
