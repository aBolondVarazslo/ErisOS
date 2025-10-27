#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>

/* Status codes */
#define STATUS_NORMAL  0
#define STATUS_SUCCESS 1
#define STATUS_FAILURE 2
#define STATUS_DEBUG   3


#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

#define TAB_WIDTH 4
#define TERMINAL_COLOUR vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK)
#define SUCCESS_COLOUR  vga_entry_colour(VGA_COLOUR_LIGHT_GREEN, VGA_COLOUR_BLACK)
#define FAILURE_COLOUR  vga_entry_colour(VGA_COLOUR_LIGHT_RED, VGA_COLOUR_BLACK)
#define DEBUG_COLOUR    vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLUE)



/* API */
void terminal_initialise(void);
void terminal_write(const char* data, size_t size, uint8_t status);
void terminal_writeString(const char* data, uint8_t status);
void terminal_typeChar(char c, uint8_t status);
void terminal_scroll(void);

#endif