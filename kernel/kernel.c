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

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint8_t success_color;
uint8_t failure_color;
uint8_t debug_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialise(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	success_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);	
	failure_color = vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
	debug_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLUE);

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_putCharAt(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_typeChar(char c, uint8_t status)
{

        if (c == '\n')
        {
                terminal_column = 0;
                terminal_row++;
        }

        else if (c == '\r')
        {
                terminal_column = 0;
		
        }

        else if (c == '\b')
        {
                terminal_column--;
        }

        else if (c == '\t')
        {
                terminal_column += 4;
        }

        else
        {

		uint8_t colour = get_colour(status);

                if (status == 0)
                        terminal_putCharAt(c, terminal_color, terminal_column, terminal_row);

                else if (status == 1)
                        terminal_putCharAt(c, success_color, terminal_column, terminal_row);

                else if (status == 2)
                        terminal_putCharAt(c, failure_color, terminal_column, terminal_row);

                else if (status == 3)
                        terminal_putCharAt(c, debug_color, terminal_column, terminal_row);

                if (++terminal_column == VGA_WIDTH) {
                        terminal_column = 0;
                        if (++terminal_row == VGA_HEIGHT)
                                terminal_row = 0;
                }
        }
}

void handle_escape(char c)
{

}

uint8_t get_colour(uint8_t status)
{
	if (status == 0)
	{
		
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

	terminal_writeString("Kernel boot successful.\n", 1);
	terminal_writeString("Attempting to load filesystem...\n", 0);
	terminal_writeString("Filesystem not found!\n", 2);
	terminal_writeString("Testing...\n", 3);
	terminal_writeString("Tabs\tend here.\n", 3);
	terminal_writeString("Backk\bspace.\n", 3);
	terminal_writeString("Not a\rReturn function.\n", 3);

	while (1 == 1)
	{
		
	}

}
