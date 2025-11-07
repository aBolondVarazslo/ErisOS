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

/* 0x03 */
void trigger_breakpoint() {
	asm volatile("int $0x03");
}