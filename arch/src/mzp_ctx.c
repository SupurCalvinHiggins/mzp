#include "mzp_ctx.h"
#include "mzp_mem.h"

void mzp_ctx_init(mzp_ctx *ctx, void start(void *), void *arg) {
  ctx->psp = (uptr)(ctx->stack + MZP_CTX_STACK_SIZE);

  mzp_ctx_cpu *cpu = (mzp_ctx_cpu *)(ctx->psp - sizeof(mzp_ctx_cpu));
  cpu->r0 = (uptr)arg;
  cpu->r1 = 0;
  cpu->r2 = 0;
  cpu->r3 = 0;
  cpu->r4 = 0;
  cpu->r5 = 0;
  cpu->r6 = 0;
  cpu->r7 = 0;
  cpu->r8 = 0;
  cpu->r9 = 0;
  cpu->r10 = 0;
  cpu->r11 = 0;
  cpu->r12 = 0;
  cpu->lr = 0; // TODO: Link to exit.
  cpu->pc = (uptr)start;
  cpu->psr = 0x01000000;
}
