#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>

/* Status codes */
#define STATUS_NORMAL  0
#define STATUS_SUCCESS 1
#define STATUS_FAILURE 2
#define STATUS_DEBUG   3

/* API */
void terminal_initialise(void);
void terminal_write(const char* data, size_t size, uint8_t status);
void terminal_writeString(const char* data, uint8_t status);
void terminal_typeChar(char c, uint8_t status);
void terminal_scroll(void);

#endif