BITS 64
GLOBAL kernel_hlt
SECTION .text
kernel_hlt:
    cli
.hlt_loop:
    hlt
    jmp .hlt_loop
