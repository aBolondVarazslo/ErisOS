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
    config &= ~0x20; /* Disable translation */

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
    terminal_writeString(scancode, STATUS_DEBUG);
    terminal_writeString("\n", STATUS_DEBUG);

    /* Todo: put buffer and process it */

    /* Send EOI */
    outb(PIC1_COMMAND, PIC_EOI);
}