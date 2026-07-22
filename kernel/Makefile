CC ?= x86_64-elf-gcc
OBJCOPY ?= x86_64-elf-objcopy
CFLAGS = -std=gnu11 -m64 -ffreestanding -O2 -Wall -Wextra -fno-builtin -Iinclude
LD ?= x86_64-elf-ld
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
	nasm -f elf64 boot/boot.asm -o boot.o

halt.o: src/halt.asm
	nasm -f elf64 src/halt.asm -o halt.o

clean:
	rm -f $(OBJ) boot.o halt.o kernel.elf kernel.bin
