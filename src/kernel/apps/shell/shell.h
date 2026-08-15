#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

#define MAX_ARGS 8
#define MAX_LINE 128

int terminal_tokenise(char *buf, char *argv[MAX_ARGS]);
void terminal_readLine(char *buf, size_t max_len);
void shell_run(void);

#endif