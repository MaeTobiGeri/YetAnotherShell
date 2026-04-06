#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

#define clear() printf("\033[H\033[J")

#define MAXLET 1000 //Maximum Number of Letters
#define MAXCOM 100 //Maximum Number of Commands

#endif
