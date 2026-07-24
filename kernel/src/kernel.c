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

static void *limine_requests[] __attribute__((used, section(".limine_reqs"))) = {
    &framebuffer_request,
    NULL
};

static void draw_framebuffer(void) {
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count == 0) {
        return;
    }

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
    if (fb == NULL || fb->address == NULL || fb->width == 0 || fb->height == 0) {
        return;
    }

    if (fb->bpp == 32) {
        volatile uint32_t *pixels = (volatile uint32_t *)fb->address;
        uint64_t count = fb->width * fb->height;
        for (uint64_t i = 0; i < count; i++) {
            pixels[i] = 0x00FF00FF;
        }
    } else if (fb->bpp == 24) {
        volatile uint8_t *pixels = (volatile uint8_t *)fb->address;
        uint64_t pitch = fb->pitch;
        for (uint64_t y = 0; y < fb->height; y++) {
            for (uint64_t x = 0; x < fb->width; x++) {
                uint64_t offset = y * pitch + x * 3;
                pixels[offset + 0] = 0xFF;
                pixels[offset + 1] = 0x00;
                pixels[offset + 2] = 0xFF;
            }
        }
    } else if (fb->bpp == 16) {
        volatile uint16_t *pixels = (volatile uint16_t *)fb->address;
        uint64_t count = (fb->pitch / 2) * fb->height;
        for (uint64_t i = 0; i < count; i++) {
            pixels[i] = 0xF81F; // magenta in 5-6-5
        }
    }
}

void kernel_main(void) {
    draw_framebuffer();
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
