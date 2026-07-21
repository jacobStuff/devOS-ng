CC = gcc
CFLAGS = -std=gnu11 -nostdinc -ffreestanding -O2 -Wall -Wextra -fno-builtin
LD = ld.lld
LDFLAGS = -nostdlib -T kernel.ld

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: kernel.bin

kernel.bin: $(OBJ) boot.o
	$(LD) $(LDFLAGS) -o kernel.elf $(OBJ) boot.o
	objcopy -O binary kernel.elf kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.o: boot/boot.asm
	nasm -f elf64 boot/boot.asm -o boot.o

clean:
	rm -f $(OBJ) boot.o kernel.elf kernel.bin
clean:
	rm -f $(OBJ) boot.o kernel.elf kernel.bin
