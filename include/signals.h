#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>

extern volatile sig_atomic_t current_child;

void handle_sigint(int sig);

#endif
