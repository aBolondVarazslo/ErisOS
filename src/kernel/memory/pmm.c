#include "pmm.h"
#include <stdbool.h>
#include <stdint.h>

extern uint32_t kernel_start;
extern uint32_t kernel_end;

/*
    1 bit per frame, packed 8 frames per byte

    Allows 262144 frames to be tracked using
    only 32KB of memory as opposed to 256KB
*/
static uint8_t frame_bitmap[MAX_FRAMES / 8];
static uint32_t highest_frame = 0;

static inline void bitmap_set(uint32_t frame) {
    frame_bitmap[frame / 8] |= (1 << (frame % 8));
}

static inline void bitmap_clear(uint32_t frame) {
    frame_bitmap[frame / 8] &= ~(1 << (frame % 8));
}

static inline bool bitmap_test(uint32_t frame) {
    return frame_bitmap[frame / 8] & (1 << (frame % 8));
}

uint32_t pmm_get_free_frame_count(void) {
    uint32_t free_count = 0;
    for (uint32_t i = 0; i < MAX_FRAMES; i++) {
        if (!bitmap_test(i)) {
            free_count++;
        }
    }
    return free_count;
}

void pmm_init(multiboot_info_t *mb_info) {
    /* Mark every frame as used by default */
    for (uint32_t i = 0; i < MAX_FRAMES; i++) {
        bitmap_set(i);
    }

    /* Walk memory map, freeing frames inside usable regions */
    multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t *)mb_info->mmap_addr;
    uint32_t offset = 0;

    while (offset < mb_info->mmap_length) {
        if (entry->type == 1) {
            uint32_t start_frame = entry->base_addr / FRAME_SIZE;
            uint32_t end_frame = (entry->base_addr + entry->length) / FRAME_SIZE;

            for (uint32_t frame = start_frame; frame < end_frame && frame < MAX_FRAMES; frame++) {
                bitmap_clear(frame);
            }

            if (end_frame > highest_frame) {
                highest_frame = end_frame;
            }
        }

        offset += entry->size + sizeof(entry->size);
        entry = (multiboot_mmap_entry_t *)((uint8_t *)entry + entry->size + sizeof(entry->size));
    }

    /* Re-reserve the frames that the kernel occupies */
    uint32_t kernel_start_frame = (uint32_t)&kernel_start / FRAME_SIZE;
    uint32_t kernel_end_frame = (uint32_t)&kernel_end / FRAME_SIZE;

    for (uint32_t frame = kernel_start_frame; frame <= kernel_end_frame; frame++) {
        bitmap_set(frame);
    }
}

uint32_t pmm_alloc_frame(void) {
    for (uint32_t i = 0; i < MAX_FRAMES; i++) {
        /* Check if the frame is free */
        if (!bitmap_test(i)) {
            /* Mark the frame as used */
            bitmap_set(i);
            return i * FRAME_SIZE;
        }
    }

    /* No free frames available */
    return PMM_INVALID_FRAME;
}

void pmm_free_frame(uint32_t frame_addr) {
    uint32_t frame = frame_addr / FRAME_SIZE;

    /* Check if the frame is valid */
    if (frame < MAX_FRAMES) {
        bitmap_clear(frame);
    }
}

uint32_t pmm_get_highest_frame(void) {
    return highest_frame;
}