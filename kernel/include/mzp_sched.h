#pragma once

#include "mzp_ctx.h"
#include "mzp_ll.h"

typedef struct {
  mzp_ctx *from_ctx;
  mzp_ctx *to_ctx;
} mzp_sched_ctx_switch;

typedef struct {
  mzp_ll threads;
} mzp_sched;

void mzp_sched_init(mzp_sched *sched);

mzp_sched_ctx_switch mzp_sched_switch(mzp_sched *sched);
