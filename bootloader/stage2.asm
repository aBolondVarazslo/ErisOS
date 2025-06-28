bits 16
org 0x10000			; Loaded at 0x1000

mov ah, 0x0E
mov al, '2'
int 0x10			; Print the character '2'


;========================
; Enable A20
;========================
enable_a20:
	in al, 0x64		; Waits until controller is ready
	test al, 2
	jnz enable_a20

	mov al, 0xAD		; Disable keyboard
	out 0x64, al


.wait_input:
	in al, 0x64
	test al, 2
	jnz .wait_input

	mov al, 0xD0		; Command: read output port
	out 0x64, al


.wait_read:
	in al, 0x64
	test al, 1
	jz .wait_read

	in al, 0x60		; Get current output port value
	or al, 00000010b	; Set A20 enable bit
	mov bl, al		; Save modified byte


.wait_ready2:
	in al, 0x64
	test al, 2
	jnz .wait_ready2

	mov al, 0xD1		; Command: write output port
	out 0x64, al


.wait_ready3:
	in al, 0x64
	test al, 2
	jnz .wait_ready3

	mov al, bl
	out 0x60, al


.wait_ready4:
	in al, 0x64
	test al, 2
	jnz .wait_ready4

	mov al, 0xAE
	out 0x64, al


call print_string


print_string:
	pusha
	mov si, msg_a20


.print_char
	lodsb			; Load byte [SI] into AL, increment SI
	or al, al		; Check if AL is 0
	jz .done

	mov ah, 0x0E
	int 0x10
	jmp .print_char

.done:
	popa
	ret

msg_a20: db " A20 Enabled.", 0
	




hang:
	cli
	hlt
	jmp hang
