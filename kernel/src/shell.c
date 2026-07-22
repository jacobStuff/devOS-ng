#include "../include/stdint.h"
extern void kernel_puts(const char *s);

void kernel_hlt(void);

void kernel_shell(void) {
    kernel_puts("devOS> ");
    kernel_hlt();
}

// Call from kernel_main if desired
