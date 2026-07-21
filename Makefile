# Simple Makefile for Limine-based kernel PoC

.PHONY: all iso clean

KDIR=kernel

all: iso

iso:
	$(MAKE) -C $(KDIR)
	mkdir -p iso/boot
	cp kernel/kernel.bin iso/boot/kernel.bin
	# Copy limine files before running
	cp limine.cfg iso/boot/limine.cfg
	cp limine.sys iso/boot/limine.sys || true
	cp limine.bin iso/boot/limine.bin || true
	# Create iso (uses xorriso)
		xorriso -as mkisofs -o iso.img -b boot/limine.bin -c boot.catalog -no-emul-boot -boot-load-size 4 -boot-info-table -isohybrid-mbr /usr/lib/ISOLINUX/isohdpfx.bin -eltorito-alt-boot -e boot/limine.cfg -no-emul-boot iso || echo "Ensure limine binaries are present"

clean:
	rm -rf iso iso.img
	$(MAKE) -C $(KDIR) clean
