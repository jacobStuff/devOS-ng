CC := $(shell command -v x86_64-elf-gcc 2>/dev/null)
LD := $(shell command -v x86_64-elf-ld 2>/dev/null)
OBJCOPY := $(shell command -v x86_64-elf-objcopy 2>/dev/null)
NASM := $(shell command -v nasm 2>/dev/null)

ifeq ($(CC),)
$(error x86_64-elf-gcc is required. Install it or use Docker.)
endif
ifeq ($(LD),)
$(error x86_64-elf-ld is required. Install it or use Docker.)
endif
ifeq ($(OBJCOPY),)
$(error x86_64-elf-objcopy is required. Install it or use Docker.)
endif
ifeq ($(NASM),)
$(error nasm is required. Install it or use Docker.)
endif

CFLAGS = -std=gnu11 -m64 -ffreestanding -O2 -Wall -Wextra -fno-builtin -Iinclude
LDFLAGS = -nostdlib -T kernel.ld

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: kernel.bin

kernel.bin: $(OBJ) boot.o halt.o
	$(LD) $(LDFLAGS) -o kernel.elf $(OBJ) boot.o halt.o
	$(OBJCOPY) -O binary kernel.elf kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.o: boot/boot.asm
	$(NASM) -f elf64 boot/boot.asm -o boot.o

halt.o: src/halt.asm
	$(NASM) -f elf64 src/halt.asm -o halt.o

clean:
	rm -f $(OBJ) boot.o halt.o kernel.elf kernel.bin
