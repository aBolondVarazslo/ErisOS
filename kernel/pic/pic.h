#ifndef PIC_H
#define PIC_H

#define PIC1    0x20    /* IO base address for master PIC */
#define PIC2    0xA0    /* IO base address for slave PIC */

#define PIC1_COMMAND    PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA   (PIC2+1)

#define PIC_EOI 0x20    /* End-of-Interrupt command code */

/* Initialisation Control Words */
#define ICW1_ICW4       0x01    /* ICW4 will be present */
#define ICW1_SINGLE     0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04    /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08    /* Level triggered (edge) mode */
#define ICW1_INIT       0x10    /* Initialisation */

#define ICW4_8086       0x01    /* 8086/8 mode */
#define ICW4_AUTO       0x02    /* Auto EOI*/
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM       0x10    /* Special fully nested */

#define CASCADE_IRQ     2

#endif