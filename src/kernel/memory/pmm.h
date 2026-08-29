#ifndef PMM_H
#define PMM_H

#include "../core/multiboot.h"
#include <stdint.h>

#define FRAME_SIZE 4096
#define MAX_FRAMES 262144 /* 1 GB of RAM */
#define PMM_INVALID_FRAME 0xFFFFFFFF

void pmm_init(multiboot_info_t *mb_info);
uint32_t pmm_alloc_frame(void);
void pmm_free_frame(uint32_t frame_addr);
uint32_t pmm_get_free_frame_count(void);
uint32_t pmm_alloc_frame(void);
void pmm_free_frame(uint32_t frame_addr);

#endif