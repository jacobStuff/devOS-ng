# Simple Makefile for Limine-based kernel PoC

ISO_TOOL := $(shell command -v xorriso 2>/dev/null || command -v genisoimage 2>/dev/null || command -v mkisofs 2>/dev/null)
ISO_CMD := $(shell if command -v xorriso >/dev/null 2>&1; then echo "xorriso -as mkisofs"; elif command -v genisoimage >/dev/null 2>&1; then echo "genisoimage"; else echo "mkisofs"; fi)

.PHONY: all iso clean

KDIR=kernel

all: iso

iso:
	$(MAKE) -C $(KDIR)
	mkdir -p iso/boot
	cp kernel/kernel.bin iso/boot/kernel.bin
	cp kernel/kernel.elf iso/boot/kernel.elf
	# Remove any stale legacy .cfg copies then copy Limine config into .conf
	rm -f iso/limine.cfg iso/boot/limine.cfg iso/boot/limine/limine.cfg || true
	cp limine.cfg iso/limine.conf
	mkdir -p iso/boot/limine
	cp limine.cfg iso/boot/limine.conf
	cp limine.cfg iso/boot/limine/limine.conf
	cp limine.sys iso/limine.sys
	cp limine.sys iso/boot/limine.sys
	cp $(if $(wildcard limine-bios.sys),limine-bios.sys,limine-binary/limine-bios.sys) iso/limine-bios.sys
	cp $(if $(wildcard limine-bios-cd.bin),limine-bios-cd.bin,limine-binary/limine-bios-cd.bin) iso/boot/limine-bios-cd.bin
	@test -n "$(ISO_TOOL)" || (echo "xorriso/genisoimage/mkisofs is required" >&2; exit 1)
	$(ISO_CMD) -o iso.img -b boot/limine-bios-cd.bin -c boot.catalog -no-emul-boot -boot-load-size 4 -boot-info-table iso

clean:
	rm -rf iso iso.img
	$(MAKE) -C $(KDIR) clean
