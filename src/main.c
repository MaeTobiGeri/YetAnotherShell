#include "common.h"
#include "signals.h"
#include "utils.h"
#include "execute.h"

int main() {
    char* buf;
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    init_shell();

    while (1) {
        buf = readline("Yash> ");
        if (!buf) break;

        if(strlen(buf) > 0) {
            add_history(buf);
            int i = 0;
            char* command[MAXCOM]; 
            char fixed[MAXLET];
            int j = 0;

            for (int k = 0; buf[k] != '\0' && j < MAXLET - 5; k++) {
                if (buf[k] == '>' && buf[k+1] == '>') {
                    fixed[j++] = ' '; 
                    fixed[j++] = '>'; 
                    fixed[j++] = '>'; 
                    fixed[j++] = ' ';
                    k++;
                } 
                else if (buf[k] == '&' && buf[k+1] == '&') {
                    fixed[j++] = ' '; 
                    fixed[j++] = '&'; 
                    fixed[j++] = '&'; 
                    fixed[j++] = ' ';
                    k++;
                }
                else if (buf[k] == '|' && buf[k+1] == '|') {
                    fixed[j++] = ' '; 
                    fixed[j++] = '|'; 
                    fixed[j++] = '|'; 
                    fixed[j++] = ' ';
                    k++;
                }
                else if (buf[k] == '>' || buf[k] == '|' || buf[k] == '<') {
                    fixed[j++] = ' '; 
                    fixed[j++] = buf[k]; 
                    fixed[j++] = ' ';
                } 
                else {
                    fixed[j++] = buf[k];
                }
            }
            fixed[j] = '\0';
            
            char* token = strtok(fixed, " ");

            while (token != NULL && i < MAXCOM - 1) {
                command[i++] = token;
                token = strtok(NULL, " ");
            }
            command[i] = NULL;

            handle_Env_Variables(command);

            int start = 0;
            int last_exec_status = 0;
            char* next_op = NULL;

            for (int k = 0; k <= i; k++) {

                if (command[k] == NULL || strcmp(command[k], "&&") == 0 || strcmp(command[k], "||") == 0) {
                    
                    char* current_op = command[k];
                    command[k] = NULL;

                    bool should_execute = true;

                    if (next_op != NULL) {
                        if (strcmp(next_op, "&&") == 0 && last_exec_status != 0) should_execute = false;
                        if (strcmp(next_op, "||") == 0 && last_exec_status == 0) should_execute = false;
                    }

                    if (should_execute) {
                        last_exec_status = execute_segment(&command[start]);
                    }

                    if (current_op == NULL) break;

                    next_op = current_op;
                    start = k + 1;
                }
            }
        }
        free(buf);
    }
    return 0;
}
