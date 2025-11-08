#include "debugging.h"

/* 0x00 */
/* Uses inline assembly rather than C to cause #DE */
void trigger_divide_error(void) {
    asm volatile("movl $1, %%eax\n\t"
                 "xorl %%edx, %%edx\n\t"
                 "idivl %%edx\n\t"
                 :
                 :
                 : "eax", "edx");
}

/* 0x01 */
void trigger_debug_exception(void) {
    asm volatile (
        "pushf\n\t"
        "pop %%eax\n\t"
        "or $0x100, %%eax\n\t"
        "push %%eax\n\t"
        "popf\n\t"
        "nop\n\t"
        "pushf\n\t"
        "pop %%eax\n\t"
        "and $~0x100, %%eax\n\t"
        "push %%eax\n\t"
        "popf\n\t"
        :
        :
        : "eax"
    );
}

/* 0x03 */
void trigger_breakpoint() {
    asm volatile("int $0x03");
}

/* 0x04 */
void trigger_overflow() {
    asm volatile (
        "movl $0x7FFFFFFF, %%eax\n\t"
        "addl $1, %%eax\n\t"
        "into\n\t"
        :
        :
        : "eax"
    );
}
