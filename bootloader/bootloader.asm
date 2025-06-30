[bits 16]
org 0x7C00

start:
	cli			; Disables interrupts

	; Setup segment registers
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00		; Temporary stack

	; Print "Booting..."
	mov si, boot_msg

.print_loop:
	lodsb
	or al, al
	jz .done_printing
	mov ah, 0x0E
	int 0x10
	jmp .print_loop

.done_printing:
	; Save boot drive number
	mov [boot_drive], dl

	; Read 1 sector (stage2)
	mov ah, 0x02
	mov al, 1
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov dl, [boot_drive]
	mov bx, 0x8000
	int 0x13
	jc disk_error

	sti			; Enable interrupts

	; Jump to stage2
	jmp 0x0000:0x8000

disk_error:
	cli
	hlt
	jmp disk_error

boot_drive: db 0
boot_msg: db "Eris Booting...", 0

times 510 - ( $ - $$ ) db 0
dw 0xAA55
