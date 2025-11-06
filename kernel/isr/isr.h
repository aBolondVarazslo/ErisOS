#ifndef ISR_H
#define ISR_H

#include <stdint.h>

/* C handler for breakpoint interrupt */
void isr_breakpoint(void);

/* Assembly stubs that IDT uses */
extern void isr_divide_error_stub(void);                 /* 0x00 */
extern void isr_debug_exception_stub(void);              /* 0x01 */
extern void isr_nmi_stub(void);                          /* 0x02 */
extern void isr_breakpoint_stub(void);                   /* 0x03 */
extern void isr_overflow_stub(void);                     /* 0x04 */
extern void isr_bound_range_exceeded_stub(void);         /* 0x05 */
extern void isr_invalid_opcode_stub(void);               /* 0x06 */
extern void isr_device_not_available_stub(void);         /* 0x07 */
extern void isr_double_fault_stub(void);                 /* 0x08 */
extern void isr_coprocessor_segment_overrun_stub(void);  /* 0x09 */
extern void isr_invalid_tss_stub(void);                  /* 0x0A */
extern void isr_segment_not_present_stub(void);          /* 0x0B */
extern void isr_stack_segment_fault_stub(void);          /* 0x0C */
extern void isr_general_protection_fault_stub(void);     /* 0x0D */
extern void isr_page_fault_stub(void);                   /* 0x0E */
extern void isr_reserved_stub(void);                     /* 0x0F */
extern void isr_x87_fpu_error_stub(void);                /* 0x10 */
extern void isr_alignment_check_stub(void);              /* 0x11 */
extern void isr_machine_check_stub(void);                /* 0x12 */
extern void isr_simd_floating_point_stub(void);          /* 0x13 */
extern void isr_virtualization_exception_stub(void);     /* 0x14 */
extern void isr_control_protection_exception_stub(void); /* 0x15 */
extern void isr_reserved_0x16_stub(void);                /* 0x16 */
extern void isr_reserved_0x17_stub(void);                /* 0x17 */
extern void isr_reserved_0x18_stub(void);                /* 0x18 */
extern void isr_reserved_0x19_stub(void);                /* 0x19 */
extern void isr_reserved_0x1A_stub(void);                /* 0x1A */
extern void isr_reserved_0x1B_stub(void);                /* 0x1B */
extern void isr_reserved_0x1C_stub(void);                /* 0x1C */
extern void isr_reserved_0x1D_stub(void);                /* 0x1D */
extern void isr_security_exception_stub(void);           /* 0x1E */
extern void isr_reserved_0x1F_stub(void);                /* 0x1F */

#endif