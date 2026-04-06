#include "common.h"
#include "execute.h"
#include "redirection.h"
#include "utils.h"
#include "signals.h"

int handle_pipe(char** command)
{
    int cmd_start[MAXCOM];
    int cmd_count = 0;

    cmd_start[cmd_count++] = 0;

    for (int i = 0; command[i] != NULL; i++) {
        if (strcmp(command[i], "|") == 0) {
            command[i] = NULL; 
            cmd_start[cmd_count++] = i + 1;
        }
    }

    int prev_fd = -1;
    pid_t pgid = 0;
    int last_pid = -1;

    for (int i = 0; i < cmd_count; i++) {
        int pipe_fds[2];

        if (i < cmd_count - 1) {
            if (pipe(pipe_fds) < 0) {
                perror("pipe");
                exit(1);
            }
        }

        int pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            if (pgid == 0) pgid = getpid();
            setpgid(0, pgid);

            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < cmd_count - 1) {
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[0]);
                close(pipe_fds[1]);
            }

            char** cmd = &command[cmd_start[i]];
            handle_input_redirection(cmd);
            handle_append(cmd);
            handle_redirection(cmd);
            execvp(cmd[0], cmd);
            perror("execvp");
            exit(1);
        }

        if (pgid == 0) pgid = pid;
        setpgid(pid, pgid);

        if (prev_fd != -1) {
            close(prev_fd);
        }
        if (i < cmd_count - 1) {
            close(pipe_fds[1]);
            prev_fd = pipe_fds[0];
        }
        last_pid = pid;
    }

    current_child = pgid;
    int status = 0;
    int last_status = 0;
    for (int i = 0; i < cmd_count; i++) {
        int wpid = wait(&status);
        if (wpid == last_pid) {
            last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
        }
    }
    if (prev_fd != -1) {
        close(prev_fd);
    }
    current_child = -1;
    return last_status;
}

void handle_Env_Variables(char** command)
{   
    for (int i = 0; command[i] != NULL; i++) 
    {
        if (command[i][0] == '$') 
        {
            char *var_name = command[i] + 1;
            char *value = getenv(var_name);
            if (value != NULL) {
                command[i] = value; 
            }
        }
    }
}

int execute_segment(char** command) {
    if (command[0] == NULL) return 0;

    if (strcmp(command[0], "exit") == 0) {
        exit(0);
    }

    else if (strcmp(command[0], "cd") == 0) {
        if (command[1] == NULL) {
            return chdir(getenv("HOME"));
        } else {
            if (chdir(command[1]) != 0) {
                perror("cd");
                return 1;
            }
            return 0;
        }
    } 
    else if (letter_Occurance(command, "|") != -1) {
        return handle_pipe(command);
    } 
    else {
        pid_t pid = fork();
        
        switch(pid) {
            case -1:
                perror("fork");
                return 1;

            case 0:
                
                struct sigaction sa_child;
                sa_child.sa_handler = SIG_DFL;
                sigemptyset(&sa_child.sa_mask);
                sa_child.sa_flags = 0;
                sigaction(SIGINT, &sa_child, NULL);

                handle_input_redirection(command);
                handle_append(command);
                handle_redirection(command); 
                execvp(command[0], command);
                perror("execvp"); 
                exit(EXIT_FAILURE);
            
            default:

                int status;
                current_child = pid;
                waitpid(pid, &status, 0);
                current_child = -1;
                return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
        }
    }
}
