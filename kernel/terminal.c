#include "terminal.h"
#include "vga.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Packs foreground and background VGA colours into a single byte */
static inline uint8_t vga_entry_colour(enum vga_colour fg, enum vga_colour bg)
{
    return fg | bg << 4;
}

/* Combines a character and a colour byte into a 16-bit VGA text buffer entry */
static inline uint16_t vga_entry(unsigned char uc, uint8_t colour)
{
    return (uint16_t) uc | (uint16_t) colour << 8;
}

/* Calculates length of null terminated string */
static size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static size_t terminal_row;
static size_t terminal_column;
static uint16_t* const terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialise(void)
{
    terminal_row = 0;
    terminal_column = 0;

    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', TERMINAL_COLOUR);
        }
    }
}

/* Returns the VGA colour bytes corresponding to the given status code */
uint8_t get_colour(uint8_t status)
{
    switch (status)
    {
        case STATUS_SUCCESS: return SUCCESS_COLOUR;
        case STATUS_FAILURE: return FAILURE_COLOUR;
        case STATUS_DEBUG:   return DEBUG_COLOUR;
        case STATUS_NORMAL:
        default:             return TERMINAL_COLOUR;
    }
}

void terminal_scroll(void)
{
    /* Moves each row up */
    for (size_t row = 1; row < VGA_HEIGHT; row++)
    {
        for (size_t col = 0; col < VGA_WIDTH; col++)
        {
            size_t dest_index = (row - 1) * VGA_WIDTH + col;
            size_t src_index = row * VGA_WIDTH + col;
            terminal_buffer[dest_index] = terminal_buffer[src_index]; /* Does the moving */
        }
    }

    /* Clear the last row */
    size_t last_row_start = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (size_t col = 0; col < VGA_WIDTH; col++)
        terminal_buffer[last_row_start + col] = vga_entry(' ', TERMINAL_COLOUR);

    terminal_row = VGA_HEIGHT - 1;
}

static void terminal_putCharAt(char c, uint8_t colour, size_t x, size_t y)
{
    if (terminal_column >= VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row++;
    }
    
    if (terminal_row >= VGA_HEIGHT)
        terminal_scroll();

    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, colour);
}

void terminal_typeChar(char c, uint8_t status)
{
    /* If newline escape character, move left and down */
    if (c == '\n')
    {
        terminal_column = 0;
        terminal_row++;

        /* Calls terminal_scroll() if terminal_row is reaches bottom of screen */
        if (terminal_row == VGA_HEIGHT)
            terminal_scroll();
    }

    else if (c == '\r')
        terminal_column = 0;
    
    else if (c == '\b')
        terminal_column--;
    
    else if (c == '\t')
        terminal_column += TAB_WIDTH;
    
    else
    {
        uint8_t colour = get_colour(status);
        terminal_putCharAt(c, colour, terminal_column, terminal_row);

        if (++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
                terminal_scroll();
        }
    }
}

void terminal_write(const char* data, size_t size, uint8_t status)
{
    for (size_t i = 0; i < size; i++)
        terminal_typeChar(data[i], status);
}

void terminal_writeString(const char* data, uint8_t status)
{
    terminal_write(data, strlen(data), status);
}