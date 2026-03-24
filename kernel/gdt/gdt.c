#include "gdt.h"
#include "../terminal.h"

struct GDTEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high
} __attribute__((packed));

struct GDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/* 0 = NULL, 1 = code, 2 = data */
static struct GDTEntry gdt[3];

static void set_gdt_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[i].base_low = (base & 0xFFFF);
    gdt[i].base_middle = (base >> 16) & 0xFF;
    gdt[i].base_high = (base >> 24) & 0xFF;
    gdt[i].limit_low = (limit & 0xFF);
    gdt[i].granularity = (limit >> 16) & 0x0F;
    gdt[i].granularity |= gran & 0xF0;
    gdt[i].access = access;
}

void gdt_init(void) {
    /* NULL descriptor */
    set_gdt_entry(0, 0, 0, 0, 0);

    /* Kernel code: 0x08 (base = 0, limit = 4GiB, 32-bit, present, ring 0, executable) */
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x92, 0xCF);

    struct GDTPointer gdtr = { sizeof(gdt) - 1, (uint32_t)&gdt };
    asm volatile("lgdt %0" : : "m"(gdtr));

    /* Far jump to reload CS with new code selector (0x08) */
    asm volatile(
        "jmp 0x08:.flush\n"
        ".flush\n"
        "mov $0x10, %ax\n"
        "mov %ax, %ds\n"
        "mov %ax, %es\n"
        "mov %ax, %fs\n"
        "mov %ax, %gs\n"
        "mov %ax, %ss\n"
    );

    terminal_writeString("GDT Loaded\n", STATUS_SUCCESS);    
}