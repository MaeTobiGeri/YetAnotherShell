#ifndef EXECUTE_H
#define EXECUTE_H

int handle_pipe(char** command);
void handle_Env_Variables(char** command);
int execute_segment(char** command);

#endif
