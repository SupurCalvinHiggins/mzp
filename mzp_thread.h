#include "mzp_int.h"
#include <stdalign.h>

#define MZP_THREAD_STACK_SIZE 1024

#define MZP_THREAD_STATE_PENDING (0 << 0)
#define MZP_THREAD_STATE_ACTIVE (1 << 0)

typedef struct {
  u32 state;
  u32 psp;
  alignas(8) u8 stack[MZP_THREAD_STACK_SIZE];
} mzp_thread;

typedef struct {
  u32 r0;
  u32 r1;
  u32 r2;
  u32 r3;
  u32 r4;
  u32 r5;
  u32 r6;
  u32 r7;
  u32 r8;
  u32 r9;
  u32 r10;
  u32 r11;
  u32 r12;
  u32 lr;
  u32 pc;
  u32 psr;
} mzp_thread_ctx;

void mzp_thread_init(mzp_thread *thread, void func(void *), void *arg);
