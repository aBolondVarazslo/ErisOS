ENTRY(start)

SECTIONS
{
    /* Set the code section starting at 0x1000 */
    . = 0x1000;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
        *(COMMON)
    }
}
