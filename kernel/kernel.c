#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks wrong operating system is being targeted. */
#if defined(__linux__)
#error "Compiler targeting Linux. Exiting."
#endif

/* Ensuring correct compiling type */
#if !defined(__i386__)
#error "Incorrect compiler. Exiting."
#endif

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

#define STATUS_NORMAL  0
#define STATUS_SUCCESS 1
#define STATUS_FAILURE 2
#define STATUS_DEBUG   3


#define TAB_WIDTH 4
#define TERMINAL_COLOUR vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK)
#define SUCCESS_COLOUR  vga_entry_colour(VGA_COLOUR_LIGHT_GREEN, VGA_COLOUR_BLACK)
#define FAILURE_COLOUR  vga_entry_colour(VGA_COLOUR_LIGHT_RED, VGA_COLOUR_BLACK)
#define DEBUG_COLOUR    vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLUE)

/* Hardware text mode colour constants. */
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

static inline uint8_t vga_entry_colour(enum vga_colour fg, enum vga_colour bg)
{
        return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t colour)
{
        return (uint16_t) uc | (uint16_t) colour << 8;
}

size_t strlen(const char* str)
{
        size_t len = 0;
        while (str[len])
                len++;
        return len;
}



size_t terminal_row;
size_t terminal_column;
uint8_t terminal_colour;
uint8_t success_colour;
uint8_t failure_colour;
uint8_t debug_colour;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialise(void)
{
        terminal_row = 0;
        terminal_column = 0;
        terminal_colour = vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
        success_colour = vga_entry_colour(VGA_COLOUR_LIGHT_GREEN, VGA_COLOUR_BLACK);
        failure_colour = vga_entry_colour(VGA_COLOUR_LIGHT_RED, VGA_COLOUR_BLACK);
        debug_colour = vga_entry_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLUE);

        for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
                for (size_t x = 0; x < VGA_WIDTH; x++)
		{
                        const size_t index = y * VGA_WIDTH + x;
                        terminal_buffer[index] = vga_entry(' ', terminal_colour);
                }
        }
}

uint8_t get_colour(uint8_t status)
{
	switch (status)
	{
		case STATUS_SUCCESS:   return SUCCESS_COLOUR;
		case STATUS_FAILURE: return FAILURE_COLOUR;
		case STATUS_DEBUG:   return DEBUG_COLOUR;
		case STATUS_NORMAL:
		default:	     return TERMINAL_COLOUR;
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

	
}

void terminal_putCharAt(char c, uint8_t colour, size_t x, size_t y)
{
        const size_t index = y * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(c, colour);
}

void terminal_typeChar(char c, uint8_t status)
{

        if (c == '\n')
        {
                terminal_column = 0;
                terminal_row++;
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
                                terminal_row = 0;
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

void kernel_main(void)
{
        /* Initialise terminal interface */
        terminal_initialise();

        terminal_writeString("Kernel boot successful.\n", STATUS_SUCCESS);
        terminal_writeString("Attempting to load filesystem...\n", STATUS_NORMAL);
        terminal_writeString("Filesystem not found!\n", 2);
        terminal_writeString("Testing...\n", 3);
        terminal_writeString("Tabs\tend here.\n", 3);
        terminal_writeString("Backk\bspace.\n", 3);
        terminal_writeString("Not a\rReturn function.\n", 3);

        while (1 == 1)
        {

        }

}
