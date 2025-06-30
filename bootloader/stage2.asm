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

hang:
    jmp hang

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

times 512 - ($ - $$) db 0
