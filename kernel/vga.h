#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

#define TAB_WIDTH 4
#define TERMINAL_COLOUR vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK)
#define SUCCESS_COLOUR  vga_entry_colour(VGA_COLOUR_LIGHT_GREEN, VGA_COLOUR_BLACK)
#define FAILURE_COLOUR  vga_entry_colour(VGA_COLOUR_LIGHT_RED, VGA_COLOUR_BLACK)
#define DEBUG_COLOUR    vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLUE)


/* Hardware text mode colour constants */
enum vga_colour {
    VGA_COLOUR_BLACK = 0,
    VGA_COLOUR_BLUE = 1,
    VGA_COLOUR_GREEN = 2,
    VGA_COLOUR_CYAN = 3,
    VGA_COLOUR_RED = 4,
    VGA_COLOUR_MAGENTA = 5,
    VGA_COLOUR_BROWN = 6,
    VGA_COLOUR_LIGHT_GREY = 7,
    VGA_COLOUR_DARK_GREY = 8,
    VGA_COLOUR_LIGHT_BLUE = 9,
    VGA_COLOUR_LIGHT_GREEN = 10,
    VGA_COLOUR_LIGHT_CYAN = 11,
    VGA_COLOUR_LIGHT_RED = 12,
    VGA_COLOUR_LIGHT_MAGENTA = 13,
    VGA_COLOUR_LIGHT_BROWN = 14,
    VGA_COLOUR_WHITE = 15,
};

#endif