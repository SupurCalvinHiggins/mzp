#include "mzp_tt.h"

void mzp_sched(void) {
  mzp_tt_hd active_hd = mzp_tt_get_active_hd();
  mzp_tt_hd hd = (active_hd + 1) & (MZP_TT_HD_MAX - 1);
  while (mzp_tt_get(hd) == 0 && hd != active_hd) {
    hd = (active_hd + 1) & (MZP_TT_HD_MAX - 1);
  }
  mzp_tt_get(active_hd)->state &= ~MZP_THREAD_STATE_ACTIVE;
  mzp_tt_get(hd)->state |= MZP_THREAD_STATE_ACTIVE;
  mzp_tt_load();
}
