#include "common.h"
#include "redirection.h"
#include "utils.h"

void handle_redirection(char** command)
{
    int redirect_index = letter_Occurance(command ,">");
    
    if (redirect_index != -1) {
        if (command[redirect_index + 1] == NULL) 
        {
            printf("Yash> syntax error near unexpected token newline\n");
            exit(EXIT_FAILURE);   
        }

        int workingFile = open(command[redirect_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (workingFile < 0) {
            perror("open");
            exit(1);
        }

        dup2(workingFile, STDOUT_FILENO);
        close(workingFile);
        command[redirect_index] = NULL;
    } 
}

void handle_append(char** command)
{
    int redirect_index = letter_Occurance(command ,">>");
    
    if (redirect_index != -1) {
        if (command[redirect_index + 1] == NULL) 
        {
            printf("Yash> syntax error near unexpected token newline\n");
            exit(EXIT_FAILURE);   
        }

        int workingFile = open(command[redirect_index + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);

        if (workingFile < 0) {
            perror("open");
            exit(1);
        }

        dup2(workingFile, STDOUT_FILENO);
        close(workingFile);
        command[redirect_index] = NULL;
    } 
}

void handle_input_redirection(char** command)
{
    int redirect_index = letter_Occurance(command ,"<");
    
    if (redirect_index != -1) {
        if (command[redirect_index + 1] == NULL) 
        {
            printf("Yash> syntax error near unexpected token newline\n");
            exit(EXIT_FAILURE);   
        }

        int workingFile = open(command[redirect_index + 1], O_RDONLY);

        if (workingFile < 0) {
            perror("open");
            exit(1);
        }

        dup2(workingFile, STDIN_FILENO);
        close(workingFile);
        command[redirect_index] = NULL;
    } 
}
