; NASM 64-bit entry for Limine
BITS 64
EXTERN kernel_main
SECTION .text
GLOBAL _start

_start:
    call kernel_main
    cli
.spin:
    hlt
    jmp .spin
