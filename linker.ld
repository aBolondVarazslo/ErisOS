ENTRY(_start)

/* Virtual base of the kernel */
KERNEL_VMA = 0xC0000000;

SECTIONS
{
	. = 2M;

	kernel_start = .;

	/* Runs with paging off */
	.boot ALIGN(4K) :
	{
		*(.multiboot)
		*(.boot.text)
		*(.boot.data)
	}

	/* Everything below is linked high */
	. += KERNEL_VMA;

	.text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VMA)
	{
		*(.multiboot)
		*(.text)
	}

	.rodata ALIGN(4K) : AT(ADDR(.rodata) - KERNEL_VMA)
	{
		*(.rodata)
	}

	.data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VMA)
	{
		*(.data)
	}

	.bss ALIGN(4K) : AT(ADDR(.bss) - KERNEL_VMA)
	{
		*(COMMON)
		*(.bss)
	}

	kernel_end = . - KERNEL_VMA;
}