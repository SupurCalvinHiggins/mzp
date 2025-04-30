#include "mzp_thread.h"
#include "mzp_mem.h"
#include <stdalign.h>

void mzp_thread_init(mzp_thread *thread, void func(void *), void *arg) {
  thread->psp = (u32)(thread->stack + MZP_THREAD_STACK_SIZE);

  mzp_thread_ctx *ctx = (mzp_thread_ctx *)(thread->sp - sizeof(mzp_thread_ctx));
  ctx->r0 = (u32)arg;
  ctx->r1 = 0;
  ctx->r2 = 0;
  ctx->r3 = 0;
  ctx->r4 = 0;
  ctx->r5 = 0;
  ctx->r6 = 0;
  ctx->r7 = 0;
  ctx->r8 = 0;
  ctx->r9 = 0;
  ctx->r10 = 0;
  ctx->r11 = 0;
  ctx->r12 = 0;
  ctx->lr = 0; // TODO: Link to exit.
  ctx->pc = (u32)func;
  ctx->psr = 0x01000000;
}
