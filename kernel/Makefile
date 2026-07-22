CC = gcc
CFLAGS = -std=gnu11 -m64 -ffreestanding -O2 -Wall -Wextra -fno-builtin -Iinclude
LD ?= ld
LDFLAGS = -nostdlib -m elf_x86_64 -T kernel.ld

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: kernel.bin

kernel.bin: $(OBJ) boot.o
	$(LD) $(LDFLAGS) -o kernel.elf $(OBJ) boot.o
	objcopy -O binary kernel.elf kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Prefer GCC/Clang assembler for portability instead of requiring nasm
boot.o: boot/boot.S
	$(CC) -c boot/boot.S -o boot.o

clean:
	rm -f $(OBJ) boot.o kernel.elf kernel.bin
