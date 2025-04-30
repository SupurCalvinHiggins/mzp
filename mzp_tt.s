.globl mzp_tt_load
.globl mzp_tt_save

.section text

mzp_tt_load:
  ; disable interrupts
  cpsid i 
  
  ; load psp
  bl mzp_tt_load_psp
  mrs r0, psp

  ; load registers
  ldmfd r0!, {r4-r11}
  msr psp, r0

  ; enable interrupts
  cpsie i

  ; return to thread
  mov lr, #0xFFFFFFFD
  bx lr

mzp_tt_save:
  ; disable interrupts
  cpsid i

  ; set r0 to thread sp
  mrs r0, psp

  ; save registers
  stmdb r0!, {r4-r11}
  msr psp, r0

  ; save psp
  bl mzp_tt_save_psp

  ; enable interrupts
  cpsie i

  j mzp_dispatch
