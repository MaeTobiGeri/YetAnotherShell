#include "common.h"
#include "signals.h"

volatile sig_atomic_t current_child = -1;

void handle_sigint(int sig) {
    if (current_child > 0) {
        kill(-current_child, SIGINT);
    } else {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();   
    }
}
