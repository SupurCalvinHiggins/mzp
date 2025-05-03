MEMORY 
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x4000
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x800
}

ENTRY(mzp_start)

SECTIONS 
{
  .text : 
  {
    KEEP(*(.ivt))
    *(.text*)
    *(.rodata*)
  } > FLASH

  .data : 
  {
    . = ALIGN(4);
    mzp_data_start = .;
    *(.data*)
    . = ALIGN(4);
    mzp_data_end = .;
  } > RAM

  .bss : 
  {
    . = ALIGN(4);
    mzp_bss_start = .;
    *(.bss*)
    . = ALIGN(4);
    mzp_bss_end = .;
  } > RAM

  .stack (NOLOAD):
  {
    . = ALIGN(8);
    mzp_stack_start = .;
    . = . + MZP_STACK_SIZE;
    . = ALIGN(8);
    mzp_stack_end = .;
  } > RAM
}
