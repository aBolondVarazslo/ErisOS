bits 16

mov ax, 0x07C0
mov ds, ax
mov ax, 0x07E0
mov ss, ax
mov sp, 0x2000		; Stack pointer decreases, so set initial stack pointer to a number
			; of bytes past the stack segment equal to the desired size of the stack

call clearscreen

push 0x0000
call movecursor
add sp, 2

push msg
call print
add sp, 2


;========================
; Loads stage2 from disk to 0x1000
;========================
mov ax, 0x1000		; Target segment
mov es, ax
xor bx, bx		; Offset into ES:BX = 0x1000:0000 = 0x10000 linear address		

mov ah, 0x02		; BIOS read sector function
mov al, 4		; Number of sectors to read
mov ch, 0		; Cylinder
mov cl, 2		; Sector (sector 1 = bootloader)
mov dh, 0		; Head
mov dl, 0x00		; Drive number (first floppy disk in VMware)

int 0x13		; BIOS interrupt
jc disk_error		; Jump if error

jmp 0x1000:0x0000	; Real mode far jump to stage2

disk_error:
	push error
	cli
	hlt
			

;========================
; Other stuff
;========================
clearscreen:
	push bp
	mov bp, sp
	pusha

	mov ah, 0x07	; Tells BIOS to scroll down window
	mov al, 0x00	; Clear entire window
	mov bh, 0x07	; White on black
	mov cx, 0x00	; Specifies top left os the screen as 0,0
	mov dh, 0x18	; 18h = 24 rows of characters
	mov dl, 0x4f	; 4fh = 79 columns of characters
	int 0x10	; Calls video interrupt

	popa
	mov sp, bp
	pop bp
	ret

movecursor:
	push bp
	mov bp, sp
	pusha

	mov dx, [bp+4]	; Get the argument from the stack. bp = 2, arg = 2
	mov ah, 0x02	; Sets cursor position
	mov bh, 0x00	; Page 0. Irrelevant
	int 0x10

	popa
	mov sp, bp
	pop bp
	ret

print:
	push bp
	mov bp, sp
	pusha
	mov si, [bp+4]	; Grabs pointer to set data
	mov bh, 0x00	; Page number, 0 again
	mov bl, 0x00	; Foreground colour. Irrelevant - in text mode
	mov ah, 0x0E	; Prints character to TTY

.char:
	mov al, [si]	; Get the current char from pointer position
	add si, 1	; Keep incrementing si until see a null character
	or al, 0
	je .return	; End if string is done
	int 0x10	; Print character if not done
	jmp .char	; Repeat

.return:
	popa
	mov sp, bp
	pop bp
	ret

msg:	db "Booting.", 0
error:	db "E", 0

times 510-($-$$) db 0
dw 0xAA55
