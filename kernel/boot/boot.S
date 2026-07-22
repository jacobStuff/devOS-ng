/* x86_64 entrypoint for the kernel */
    .text
    .global _start
    .type _start, @function
_start:
    call kernel_main
    cli
.spin:
    hlt
    jmp .spin
