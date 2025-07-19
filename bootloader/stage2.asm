[bits 16]
org 0x8000

start:
    ; Setup stack
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFFFF

    call enable_a20

    ; Print 'A' to signal success
    mov al, 'A'
    mov ah, 0x0E
    int 0x10

    call switch_to_pm

enable_a20:
    call wait_input_clear

    mov al, 0xAD            ; Disable keyboard
    out 0x64, al

    call wait_input_clear

    mov al, 0xD0            ; Read output port
    out 0x64, al
    call wait_output_ready
    in al, 0x60
    push ax

    call wait_input_clear
    mov al, 0xD1            ; Write output port
    out 0x64, al
    call wait_input_clear

    pop ax
    or al, 2                ; Enable A20 bit
    out 0x60, al

    call wait_input_clear
    mov al, 0xAE            ; Enable keyboard
    out 0x64, al

    ret

wait_input_clear:
    in al, 0x64
    test al, 2              ; bit 1 = input buffer full
    jnz wait_input_clear
    ret

wait_output_ready:
    in al, 0x64
    test al, 1              ; bit 0 = output buffer full
    jz wait_output_ready
    ret

; --- GDT Setup ---
gdt_start:
    ; Null descriptor
    dq 0x0000000000000000

    ; Code segment: base=0, limit=4GB, type=0x9A (executable, readable, accessed), granularity=4K, 32-bit
    dq 0x00CF9A000000FFFF

    ; Data segment: base=0, limit=4GB, type=0x92 (writable, accessed), granularity=4K, 32-bit
    dq 0x00CF92000000FFFF

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1   ; Limit (size of GDT - 1)
    dd gdt_start                 ; Base address of GDT

; --- End GDT Setup ---

; --- Enter Protected Mode ---
switch_to_pm:
    cli                         ; Disable interrupts

    lgdt [gdt_descriptor]       ; Load GDT

    mov eax, cr0
    or eax, 1                   ; Set PE bit (Protection Enable)
    mov cr0, eax

    ; Far jump to flush pipeline and load CS
    jmp 0x08:protected_mode     ; 0x08 = code segment selector

; This is now running in 32-bit protected mode
[bits 32]
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Initialize serial port (COM1, 0x3F8)
    mov dx, 0x3F8      ; COM1 base port
    mov al, 0x00
    out dx, al         ; Disable interrupts

    mov dx, 0x3FB      ; Line control register
    mov al, 0x80
    out dx, al         ; Enable DLAB

    mov dx, 0x3F8      ; Set baud rate divisor to 3 (38400 baud)
    mov al, 0x03
    out dx, al
    mov dx, 0x3F9
    xor al, al
    out dx, al

    mov dx, 0x3FB
    mov al, 0x03
    out dx, al         ; 8 bits, no parity, one stop bit

    mov dx, 0x3F9
    mov al, 0xC7
    out dx, al         ; Enable FIFO, clear them, 14-byte threshold

    mov dx, 0x3FA
    mov al, 0x0B
    out dx, al         ; IRQs enabled, RTS/DSR set

    ; Send 'G' over serial (for debugging)
    mov dx, 0x3F8
.wait_serial:
    in al, 0x3FD
    test al, 0x20
    jz .wait_serial
    mov al, 'G'
    out dx, al

pm_hang:
    jmp pm_hang

times 512 - ($ - $$) db 0
