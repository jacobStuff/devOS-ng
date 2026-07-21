; Minimal 64-bit entry that calls kernel_main
[bits 64]
[extern kernel_main]
[section .text]
global _start
_start:
    ; Use limine-provided entry; just jump to kernel_main
    call kernel_main
    cli
.hang:
    hlt
    jmp .hang
