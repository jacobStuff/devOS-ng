# Simple Makefile for Limine-based kernel PoC

ISO_TOOL := $(shell command -v xorriso 2>/dev/null || command -v genisoimage 2>/dev/null || command -v mkisofs 2>/dev/null)

.PHONY: all iso clean

KDIR=kernel

all: iso

iso:
	$(MAKE) -C $(KDIR)
	mkdir -p iso/boot
	cp kernel/kernel.bin iso/boot/kernel.bin
	# Copy Limine files before running
	@test -f limine.cfg || (echo "limine.cfg missing" >&2; exit 1)
	@test -f limine.sys || (echo "limine.sys missing" >&2; exit 1)
	@test -f limine.bin || (echo "limine.bin missing" >&2; exit 1)
	cp limine.cfg iso/boot/limine.cfg
	cp limine.sys iso/boot/limine.sys
	cp limine.bin iso/boot/limine.bin
	@test -n "$(ISO_TOOL)" || (echo "xorriso/genisoimage/mkisofs is required" >&2; exit 1)
	$(ISO_TOOL) -o iso.img -b boot/limine.bin -c boot.catalog -no-emul-boot -boot-load-size 4 -boot-info-table -isohybrid-mbr /usr/lib/ISOLINUX/isohdpfx.bin -eltorito-alt-boot -e boot/limine.cfg -no-emul-boot iso
	rm -rf iso iso.img
	$(MAKE) -C $(KDIR) clean
