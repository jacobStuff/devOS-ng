#include "../include/stdint.h"

void kernel_puts(const char *s);

void kernel_shell(void);

void kernel_main(void) {
    kernel_puts("Hello from devOS kernel!\n");
    kernel_puts("Starting simple shell...\n");
    kernel_shell();
    for(;;) __asm__("hlt");
}

// Very small VGA text-mode writer for early PoC
static volatile uint16_t *VGA = (volatile uint16_t*)0xB8000;
static int row = 0, col = 0;

void kernel_puts(const char *s) {
    while (*s) {
        if (*s == '\n') { row++; col=0; s++; continue; }
        VGA[row*80 + col] = (uint16_t)(0x0F << 8) | *s;
        col++;
        if (col >= 80) { col=0; row++; }
        s++;
    }
}
