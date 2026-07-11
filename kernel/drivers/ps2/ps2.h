#ifndef PS2_H
#define PS2_H

#include <stdint.h>

/* PS2 Ports */
#define PS2_DATA_PORT       0x60
#define PS2_COMMAND_PORT    0x64

/* PS2 Commands */
#define PS2_CMD_READ_CONFIG     0x20
#define PS2_CMD_WRITE_CONFIG    0x60
#define PS2_CMD_DISABLE_PORT1   0xAD
#define PS2_CMD_ENABLE_PORT1    0xAE
#define PS2_CMD_DISABLE_PORT2   0xA7
#define PS2_CMD_ENABLE_PORT2    0xA8
#define PS2_CMD_TEST_CONTROLLER 0xAA
#define PS2_CMD_TEST_PORT1      0xAB

/* Status flags */
#define PS2_STATUS_OUTPUT_FULL  0x01
#define PS2_STATUS_INPUT_FULL   0x02

void ps2_init(void);
void ps2_keyboard_handler(void);

/* Optional helper functions */
uint8_t ps2_read_data(void);
void ps2_send_command(uint8_t cmd);
void ps2_send_data(uint8_t data);

#endif