#include "thread.h"

thread_hd thread_create(void func(void *), void *arg) {
  return mzp_thread_create(func, arg);
}

void thread_join(thread_hd thread_hd) { mzp_thread_join(thread_hd); }

void thread_yield(void) { mzp_thread_yield(); }

void thread_exit(void) { mzp_thread_exit(); }
