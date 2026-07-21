/* Fallback assembly entry for older toolchains */
.global _start
_start:
    call kernel_main
    cli
1: hlt
    jmp 1b
