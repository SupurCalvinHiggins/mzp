#include "mzp_tt.h"
#include "mzp_assert.h"
#include "mzp_mem.h"
#include "mzp_thread.h"

i32 mzp_tt_hd_free_top;
mzp_tt_hd mzp_tt_hd_free[MZP_TT_HD_MAX];

void mzp_tt_hd_free_init(void) {
  mzp_tt_hd_free_top = MZP_TT_HD_MAX - 1;
  for (u32 i = 0; i < MZP_TT_HD_MAX; ++i) {
    mzp_tt_hd_free[i] = i;
  }
}

mzp_tt_hd mzp_tt_hd_free_pop(void) {
  mzp_assert(mzp_tt_hd_free_top >= 0);
  mzp_tt_hd hd = mzp_tt_hd_free[mzp_tt_hd_free_top];
  --mzp_tt_hd_free_top;
  return hd;
}

void mzp_tt_hd_free_push(mzp_tt_hd hd) {
  mzp_assert(mzp_tt_hd_free_top < MZP_TT_HD_MAX - 1);
  ++mzp_tt_hd_free_top;
  mzp_tt_hd_free[mzp_tt_hd_free_top] = hd + MZP_TT_HD_MAX;
}

mzp_mem_allocator_hd mzp_tt_allocator_hd; // TODO: Allocate mzp_thread.
mzp_thread *mzp_tt[MZP_TT_HD_MAX];

void mzp_tt_init(void) {
  mzp_tt_hd_free_init();
  for (u32 i = 0; i < MZP_TT_HD_MAX; ++i) {
    mzp_tt[i] = 0;
  }
}

mzp_thread *mzp_tt_get(mzp_tt_hd hd) {
  u32 idx = hd & (MZP_TT_HD_MAX - 1);
  return mzp_tt[idx];
}

void mzp_tt_set(mzp_tt_hd hd, mzp_thread *thread) {
  mzp_assert(mzp_tt_get(hd) == 0);
  u32 idx = hd & (MZP_TT_HD_MAX - 1);
  mzp_tt[idx] = thread;
}

mzp_tt_hd mzp_tt_spawn(void func(void *), void *arg) {
  mzp_thread *thread = (mzp_thread *)mzp_mem_alloc(mzp_tt_allocator_hd);
  mzp_thread_init(thread, func, arg);
  mzp_tt_hd hd = mzp_tt_hd_free_pop();
  mzp_tt_set(hd, thread);
  return hd;
}

mzp_tt_hd mzp_tt_get_active_hd(void) {
  for (u32 i = 0; i < MZP_TT_HD_MAX; ++i) {
    if (mzp_tt_get(i)->state & MZP_THREAD_STATE_ACTIVE) {
      return i;
    }
  }
  mzp_assert(0);
  while (1)
    ;
}

void mzp_tt_save_psp(u32 psp) {
  mzp_tt_hd active_hd = mzp_tt_get_active_hd();
  mzp_tt_get(active_hd)->psp = psp;
}

u32 mzp_tt_load_psp(void) {
  mzp_tt_hd active_hd = mzp_tt_get_active_hd();
  return mzp_tt_get(active_hd)->psp;
}
