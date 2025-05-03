.syntax unified
.arch armv6-m

.section .text
.align 4
.globl mzp_start
mzp_start:
  // zero bss
  ldr r0, =mzp_bss_start
  ldr r1, =mzp_bss_end
  ldr r2, =0

mzp_bss_clear_start:
  cmp r0, r1
  beq mzp_bss_clear_end
  str r2, [r0]
  adds r0, #4
  b mzp_bss_clear_start
mzp_bss_clear_end:

  b mzp_main

hang:
  b hang
