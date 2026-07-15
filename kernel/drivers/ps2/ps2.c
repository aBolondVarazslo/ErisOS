#include "ps2.h"
#include "../io/io.h"
#include "../pic/pic.h"
#include "../../lib/terminal.h"
#include <stdbool.h>

static bool ps2_ready = false;

/* Simple circular buffer for scan codes */
#define PS2_BUFFER_SIZE 32
static uint8_t ps2_buffer[PS2_BUFFER_SIZE];
static uint8_t buffer_head = 0;
static uint8_t buffer_tail = 0;

static bool shift_held = false;
static bool caps_lock_on = false;
static bool break_flag = false; /* true = next byte is release */

/* Unshifted keymap, indexed by Set 2 scan code */
static const char keymap_lower[128] = {
    ['\x1C'] = 'a', ['\x32'] = 'b', ['\x21'] = 'c', ['\x23'] = 'd',
    ['\x24'] = 'e', ['\x2B'] = 'f', ['\x34'] = 'g', ['\x33'] = 'h',
    ['\x43'] = 'i', ['\x3B'] = 'j', ['\x42'] = 'k', ['\x4B'] = 'l',
    ['\x3A'] = 'm', ['\x31'] = 'n', ['\x44'] = 'o', ['\x4D'] = 'p',
    ['\x15'] = 'q', ['\x2D'] = 'r', ['\x1B'] = 's', ['\x2C'] = 't',
    ['\x3C'] = 'u', ['\x2A'] = 'v', ['\x1D'] = 'w', ['\x22'] = 'x',
    ['\x35'] = 'y', ['\x1A'] = 'z',

    ['\x45'] = '0', ['\x16'] = '1', ['\x1E'] = '2', ['\x26'] = '3',
    ['\x25'] = '4', ['\x2E'] = '5', ['\x36'] = '6', ['\x3D'] = '7',
    ['\x3E'] = '8', ['\x46'] = '9',

    ['\x0E'] = '`', ['\x4E'] = '-', ['\x55'] = '=',
    ['\x54'] = '[', ['\x5B'] = ']', ['\x5D'] = '\\',
    ['\x4C'] = ';', ['\x52'] = '\'', ['\x41'] = ',',
    ['\x49'] = '.', ['\x4A'] = '/',

    ['\x29'] = ' ',  ['\x5A'] = '\n', ['\x66'] = '\b', ['\x0D'] = '\t',
};

/* Shifted keymap, indexed by Set 2 scan code */
static const char keymap_upper[128] = {
    ['\x1C'] = 'A', ['\x32'] = 'B', ['\x21'] = 'C', ['\x23'] = 'D',
    ['\x24'] = 'E', ['\x2B'] = 'F', ['\x34'] = 'G', ['\x33'] = 'H',
    ['\x43'] = 'I', ['\x3B'] = 'J', ['\x42'] = 'K', ['\x4B'] = 'L',
    ['\x3A'] = 'M', ['\x31'] = 'N', ['\x44'] = 'O', ['\x4D'] = 'P',
    ['\x15'] = 'Q', ['\x2D'] = 'R', ['\x1B'] = 'S', ['\x2C'] = 'T',
    ['\x3C'] = 'U', ['\x2A'] = 'V', ['\x1D'] = 'W', ['\x22'] = 'X',
    ['\x35'] = 'Y', ['\x1A'] = 'Z',

    ['\x45'] = ')', ['\x16'] = '!', ['\x1E'] = '"', ['\x26'] = 0,
    ['\x25'] = '$', ['\x2E'] = '%', ['\x36'] = '^', ['\x3D'] = '&',
    ['\x3E'] = '*', ['\x46'] = '(',

    ['\x0E'] = 0,   ['\x4E'] = '_', ['\x55'] = '+',
    ['\x54'] = '{', ['\x5B'] = '}', ['\x5D'] = '|',
    ['\x4C'] = ':', ['\x52'] = '@', ['\x41'] = '<',
    ['\x49'] = '>', ['\x4A'] = '?',

    ['\x29'] = ' ',  ['\x5A'] = '\n', ['\x66'] = '\b', ['\x0D'] = '\t',
};

static inline bool ps2_buffer_full(void) {
    return ((buffer_head + 1) % PS2_BUFFER_SIZE) == buffer_tail;
}

static inline bool ps2_buffer_empty(void) {
    return buffer_head == buffer_tail;
}

static void ps2_buffer_push(uint8_t c) {
    if (ps2_buffer_full()) {
        return; /* Buffer is full so char is dtopped */
    }
    ps2_buffer[buffer_head] = c;
    buffer_head = (buffer_head + 1) % PS2_BUFFER_SIZE;
}

/* PS2 Controller functions */
uint8_t ps2_read_data(void) {
    while (!(inb(PS2_COMMAND_PORT) & PS2_STATUS_OUTPUT_FULL)) {
        /* Wait */
    }
    return inb(PS2_DATA_PORT);
}

void ps2_send_command(uint8_t cmd) {
    while (inb(PS2_COMMAND_PORT) & PS2_STATUS_INPUT_FULL) {
        /* Wait */
    }
    outb(PS2_COMMAND_PORT, cmd);
}

void ps2_send_data(uint8_t data) {
    while (inb(PS2_COMMAND_PORT) & PS2_STATUS_INPUT_FULL) {
        /* Wait */
    }
    outb(PS2_DATA_PORT, data);
}

/* Main initialisation */
void ps2_init(void) {
    /* Disable both PS2 ports */
    ps2_send_command(PS2_CMD_DISABLE_PORT1);
    ps2_send_command(PS2_CMD_DISABLE_PORT2);

    /* Flush output buffer */
    while (inb(PS2_COMMAND_PORT) & PS2_STATUS_OUTPUT_FULL) {
        inb(PS2_DATA_PORT);
    }

    /* Read current config byte */
    ps2_send_command(PS2_CMD_READ_CONFIG);
    uint8_t config = ps2_read_data();

    /* Enable IRQ1 (keyboard), disable IRQ12 (mouse) */
    config |= 0x01;  /* Enable keyboard interrupt */
    config &= ~0x02; /* Disable mouse interrupt */
    config &= ~0x40; /* Disable translation */

    ps2_send_command(PS2_CMD_WRITE_CONFIG);
    ps2_send_data(config);

    /* Enable keyboard port */
    ps2_send_command(PS2_CMD_ENABLE_PORT1);

    /* Self test */
    ps2_send_command(PS2_CMD_TEST_CONTROLLER);
    if (ps2_read_data() != 0x55) {
        terminal_writeString("PS2 Controller self-test failed!\n", STATUS_FAILURE);
        return;
    }

    ps2_ready = true;
    terminal_writeString("PS2 Controller initialised\n", STATUS_SUCCESS);
}

/* IRQ Handler */
void ps2_keyboard_handler(void) {
    if (!ps2_ready) {
        outb(PIC1_COMMAND, PIC_EOI);
        return;
    }

    uint8_t scancode = inb(PS2_DATA_PORT);
    
    if (scancode == 0xF0) {
        break_flag = true;
        outb(PIC1_COMMAND, PIC_EOI);
        return; /* Wait for next interrupt */
    }
    
    if (break_flag) {
        /* This scancode is a RELEASE */
        if (scancode == 0x12 || scancode == 0x59) {
            shift_held = false;
        }
        break_flag = false;
    } else {
        /* This scancode is a PRESS */
        /* Left shift and Right shift respectively */
        if (scancode == 0x12 || scancode == 0x59) {
            shift_held = true;
        }
        
        /* Caps lock */
        else if (scancode == 0x58) {
            caps_lock_on = !caps_lock_on;
        } else {
            /* Variable to store character pressed */
            char c;
            if (shift_held || caps_lock_on) {
                c = keymap_upper[scancode];
            } else {
                c = keymap_lower[scancode];
            }
            
            if (c != 0) {
                ps2_buffer_push(c);
                terminal_typeChar(c, STATUS_NORMAL);
            }
        }
    }
    /* Send EOI */
    outb(PIC1_COMMAND, PIC_EOI);
}