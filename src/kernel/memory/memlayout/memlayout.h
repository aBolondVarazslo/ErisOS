#ifndef MEMLAYOUT_H
#define MEMLAYOUT_H

#include <stdint.h>

#define KERNEL_VMA 0xC0000000
#define PHYS_TO_VIRT(addr) ((uint32_t)(addr) + KERNEL_VMA)
#define VIRT_TO_PHYS(addr) ((uint32_t)(addr) - KERNEL_VMA)

#endif