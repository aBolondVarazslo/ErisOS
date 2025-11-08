#ifndef DEBUGGING_H
#define DEBUGGING_H

/* Trigger CPU exceptions for testing ISR handlers */

void trigger_divide_error(void);    /* Divide error (0x00) */
void trigger_debug_exception(void); /* Debug exception (0x01) */
void trigger_breakpoint(void);      /* Breakpoint (0x03) */
void trigger_overflow(void);        /* Overflow (0x04) */

#endif