#include "mzp_sched.h"
#include "mzp_assert.h"
#include "mzp_ll.h"

void mzp_sched_init(mzp_sched *sched);

mzp_sched_ctx_switch mzp_sched_switch(mzp_sched *sched) {
  mzp_assert(mzp_ll_len(&sched->threads) != 0);
  if (mzp_ll_len(&sched->threads) == 1) {
    mzp_ctx *ctx = mzp_ll_peek_front(&sched->threads);
    return (mzp_sched_ctx_switch){ctx, ctx};
  }

  mzp_ctx *from_ctx = mzp_ll_pop_front(&sched->threads);
  mzp_ll_push_back(&sched->threads, from_ctx);
  mzp_ctx *to_ctx = mzp_ll_peek_front(&sched->threads);

  return (mzp_sched_ctx_switch){from_ctx, to_ctx};
}
