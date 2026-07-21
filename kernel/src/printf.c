#include <stdarg.h>
#include <stdint.h>

extern void kernel_puts(const char *s);

void kprint_hex(uint64_t x) {
    char buf[17]; buf[16]='\0';
    for (int i=15;i>=0;i--) { int v = x & 0xF; buf[i] = (v < 10) ? ('0'+v) : ('a'+v-10); x >>=4; }
    kernel_puts(buf);
}

void kputs(const char *s) { kernel_puts(s); }

int kprintf(const char *fmt, ...) { (void)fmt; return 0; }
