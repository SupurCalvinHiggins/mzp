#pragma once

#define mzp_assert(expr)                                                       \
  (void)((expr) || (mzp_assert_impl(#expr, __FILE__, __LINE__), 0))

void mzp_assert_impl(const char *expr, const char *file, int line);
