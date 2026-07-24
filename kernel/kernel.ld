OUTPUT_FORMAT("elf64-x86-64")
ENTRY(_start)
SECTIONS
{
  . = 0xffffffff80000000;
  .text : { *(.text*) }
  .limine_reqs : { *(.limine_reqs) }
  .rodata : { *(.rodata*) }
  .data : { *(.data*) }
  .bss : { *(.bss*) }
}
