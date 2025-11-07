#include "idt.h"
#include "../terminal.h"
#include "../vga.h"
#include "../isr/isr.h"

/* IDT */
struct IDTEntry idt[256];
struct IDTPointer idt_ptr;

/* Fills one IDT entry */
void set_idt_entry(int n, uint32_t handler, uint16_t selector, uint8_t flags) {
	idt[n].offset_low = handler & 0xFFFF;
	idt[n].selector = selector;
	idt[n].zero = 0;
	idt[n].flags = flags;
	idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

/* Initialise IDT */
void idt_init() {
	idt_ptr.limit = sizeof(idt) - 1;
	idt_ptr.base = (uint32_t)&idt;

	uint16_t cs16;
	asm volatile("mov %%cs, %0" : "=r"(cs16));
	set_idt_entry(IDT_DIVIDE_ERROR, (uint32_t)isr_divide_error_stub, cs16, IDT_FLAG_KERNEL_INTERRUPT);
	set_idt_entry(IDT_BREAKPOINT, (uint32_t)isr_breakpoint_stub, cs16, IDT_FLAG_KERNEL_INTERRUPT);

	/* Load IDT */
	asm volatile("lidt %0" : : "m"(idt_ptr));
	terminal_writeString("IDT Initialised.\n", STATUS_SUCCESS);
}