This project targets a Linux cross-build environment; macOS's assembler and toolchain can reject raw x86_64 directives.

Recommended: build inside an Ubuntu Docker container with required tools:

```bash
docker run --rm -it -v "$PWD":/work -w /work ubuntu:24.04 bash
apt update && apt install -y build-essential nasm xorriso binutils gcc-12 g++-12 clang-18 lld-18
make -C kernel
```

Alternatively, install `nasm` and a proper x86_64 cross-toolchain on macOS (Homebrew: `brew install nasm gcc binutils`), or use a Linux VM.
