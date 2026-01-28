.section .text

.intel_syntax noprefix
.code32

/* IRQ0 – Timer (0x20) */
.global irq0_stub
.type irq0_stub, @function
irq0_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 32
    call irq_common_handler

/* IRQ1 – Keyboard (0x21) */
.global irq1_stub
.type irq1_stub, @function
irq1_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 33
    call irq_common_handler

/* IRQ2 – Cascade (0x22) */
.global irq2_stub
.type irq2_stub, @function
irq2_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 34
    call irq_common_handler

/* IRQ3–IRQ15 */
.global irq3_stub
.type irq3_stub, @function
irq3_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 35
    call irq_common_handler

.global irq4_stub
.type irq4_stub, @function
irq4_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 36
    call irq_common_handler

.global irq5_stub
.type irq5_stub, @function
irq5_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 37
    call irq_common_handler

.global irq6_stub
.type irq6_stub, @function
irq6_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 38
    call irq_common_handler

.global irq7_stub
.type irq7_stub, @function
irq7_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 39
    call irq_common_handler

.global irq8_stub
.type irq8_stub, @function
irq8_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 40
    call irq_common_handler

.global irq9_stub
.type irq9_stub, @function
irq9_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 41
    call irq_common_handler

.global irq10_stub
.type irq10_stub, @function
irq10_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 42
    call irq_common_handler

.global irq11_stub
.type irq11_stub, @function
irq11_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 43
    call irq_common_handler

.global irq12_stub
.type irq12_stub, @function
irq12_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 44
    call irq_common_handler

.global irq13_stub
.type irq13_stub, @function
irq13_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 45
    call irq_common_handler

.global irq14_stub
.type irq14_stub, @function
irq14_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 46
    call irq_common_handler

.global irq15_stub
.type irq15_stub, @function
irq15_stub:
    push 0
    lea eax, [esp + 4]
    push eax
    push 47
    call irq_common_handler