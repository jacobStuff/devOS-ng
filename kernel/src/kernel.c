#include <stddef.h>
#include "../include/stdint.h"
#include "../include/limine.h"

void kernel_puts(const char *s);

void kernel_shell(void);

void kernel_hlt(void);

static struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
    .response = NULL
};

void kernel_main(void) {
    if (framebuffer_request.response != NULL && framebuffer_request.response->framebuffer_count > 0) {
        struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
        uint32_t *pixels = (uint32_t *)fb->address;
        uint64_t count = fb->width * fb->height;
        for (uint64_t i = 0; i < count; i++) {
            pixels[i] = 0x00101010;
        }
    }

    kernel_puts("Hello from devOS kernel!\n");
    kernel_puts("Starting simple shell...\n");
    kernel_shell();
    kernel_hlt();
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
