#include "mzp_int.h"
#include "mzp_thread.h"

// NOTE: Must be a power of 2.
#define MZP_TT_HD_MAX 16

typedef u32 mzp_tt_hd;

void mzp_tt_init(void);
mzp_tt_hd mzp_tt_get_active_hd(void);
mzp_thread *mzp_tt_get(mzp_tt_hd hd);
mzp_tt_hd mzp_tt_spawn(void func(void *), void *arg);

void mzp_tt_load(void);
void mzp_tt_save(void);

void mzp_tt_save_psp(u32 psp);
u32 mzp_tt_load_psp(void);
