#ifndef ISR_H
#define ISR_H

#include <stdint.h>

/* C handler for breakpoint interrupt */
void isr_breakpoint(void);

/* Assembly stub that IDT uses */
extern void isr_breakpoint_stub(void);

#endif