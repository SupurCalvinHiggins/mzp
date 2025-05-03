.globl mzp_ctx_switch
.section text

mzp_ctx_switch:
  // disable interrupts
  cpsid i 

  // if no switch, fast exit 
  tst r0, r1
  beq exit

  // set r2 to from_ctx psp
  mrs r2, psp

  // stack from_ctx registers
  stmdb r2!, {r4-r11}

  // save from_ctx psp
  str r2, [r0, #0]

  // set r2 to to_ctx psp
  ldr r2, [r1, #0]

  // unstack to_ctx registers
  ldmfd r2!, {r4-r11}

  // load to_ctx psp
  msr psp, r2

exit:
  // set thread mode
  mov lr, #0xFFFFFFFD

  // enable interrupts
  cpsie i

  // return to to_ctx 
  bx lr
