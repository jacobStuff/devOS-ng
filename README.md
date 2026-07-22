Developer OS Proof-of-Concept

This repository contains a minimal OS proof-of-concept that boots with the Limine bootloader and provides a simple kernel and shell.

Quick start (Linux/macOS with QEMU):

```bash
# Build
make

# Boot in QEMU
qemu-system-x86_64 -cdrom iso.img -m 512M
```

Notes:
- Download Limine binaries and place `limine.sys`, `limine.bin`, and `limine-eltorito-*.bin` in the repo root before running `make iso`.
- This project uses `nasm` for the boot entry and a cross x86_64 toolchain for linking.
- On macOS, install `nasm` and an x86_64 ELF toolchain, or use Docker as documented in `DOCKER.md`.
- See `kernel/` for sources.
