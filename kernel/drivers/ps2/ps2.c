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

/* Unshifted keymap, indexed by Set 1 scan code */
static const char keymap_lower[128] = {
    /* 0x00 */ 0,    27,  '1', '2', '3', '4', '5', '6',
    /* 0x08 */ '7',  '8', '9', '0', '-', '=', '\b', '\t',
    /* 0x10 */ 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    /* 0x18 */ 'o', 'p', '[', ']', '\n', 0 /* ctrl */, 'a', 's',
    /* 0x20 */ 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    /* 0x28 */ '\'', '`', 0 /* lshift */, '\\', 'z', 'x', 'c', 'v',
    /* 0x30 */ 'b', 'n', 'm', ',', '.', '/', 0 /* rshift */, '*',
    /* 0x38 */ 0 /* alt */, ' ', 0 /* capslock */,
    /* Put function keys, numpad, etc here in future */
};

/* Shifted keymap, indexed by Set 1 scan code */
static const char keymap_upper[128] = {
    /* 0x00 */ 0,    27,  '!', '"', '£', '$', '%', '^',
    /* 0x08 */ '&',  '*', '(', ')', '_', '+', '\b', '\t',
    /* 0x10 */ 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    /* 0x18 */ 'O', 'P', '{', '}', '\n', 0 /* CTRL */, 'A', 'S',
    /* 0x20 */ 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    /* 0x28 */ '@', '¬', 0 /* Left shift */, '|', 'Z', 'X', 'C', 'V',
    /* 0x30 */ 'B', 'N', 'M', '<', '>', '?', 0 /* Right shift */, '*',
    /* 0x38 */ 0 /* alt */, ' ', 0 /* Caps lock */,
    /* Put function keys, numpad, etc here in future */
};

static inline bool ps2_buffer_full(void) {
    return ((buffer_head + 1) % PS2_BUFFER_SIZE) == buffer_tail;
}

static inline bool ps2_buffer_empty(void) {
    return buffer_head == buffer_tail;
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

    /* Basic output */
    terminal_writeString("Scan: ", STATUS_DEBUG);
    terminal_writeHex(scancode);
    
    if (scancode & 0x80) {
        terminal_writeString(" (release)\n", STATUS_DEBUG);
    } else {
        terminal_writeString(" (press)\n", STATUS_DEBUG);
    }

    /* Todo: put buffer and process it */

    /* Send EOI */
    outb(PIC1_COMMAND, PIC_EOI);
}