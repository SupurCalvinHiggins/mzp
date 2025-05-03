#pragma once

#include "mzp_int.h"
#include <stdalign.h>

#define MZP_CTX_STACK_SIZE 1024

typedef struct {
  u32 psp;
  alignas(8) u8 stack[MZP_CTX_STACK_SIZE];
} mzp_ctx;

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
} mzp_ctx_cpu;

void mzp_ctx_init(mzp_ctx *ctx, void start(void *), void *arg);
void mzp_ctx_switch(mzp_ctx *ctx_from, mzp_ctx *ctx_to);
