#ifndef TOKENIZER_H_
#define TOKENIZER_H_



void redirection(char **argv);
int tokenstr(char *buf, char del, char **argv);
void parseLine(char *line, char **argv);

#endif /* TOKENIZER_H_ */
