#include <stdint.h>
extern void kernel_puts(const char *s);

void kernel_shell(void) {
    kernel_puts("devOS> ");
    for(;;) __asm__("hlt");
}

// Call from kernel_main if desired
