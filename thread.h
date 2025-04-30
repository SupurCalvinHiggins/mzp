#include "mzp_thread.h"

typedef mzp_thread_hd thread_hd;

thread_hd thread_create(void func(void *), void *arg);
void thread_join(thread_hd thread_hd);
void thread_yield(void);
void thread_exit(void);
