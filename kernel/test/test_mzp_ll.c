#include "mzp_assert.h"
#include "mzp_ll.h"
#include "mzp_mem.h"

void test_mzp_ll_init(void) {
  MZP_MEM_ALLOCATOR(ll_allocator, mzp_ll_node, 3);

  mzp_ll ll;
  mzp_ll_init(&ll, &ll_allocator);
  mzp_assert(mzp_ll_len(&ll) == 0);
}

void test_mzp_ll_new(void) {
  MZP_MEM_ALLOCATOR(ll_allocator, mzp_ll_node, 3);

  mzp_ll ll = mzp_ll_new(&ll_allocator);
  mzp_assert(mzp_ll_len(&ll) == 0);
}

void test_mzp_ll_push_front(void) {
  MZP_MEM_ALLOCATOR(ll_allocator, mzp_ll_node, 3);

  mzp_ll ll = mzp_ll_new(&ll_allocator);
  mzp_ll_push_front(&ll, (void *)0xDEAD3333);
  mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_len(&ll) == 1);

  mzp_ll_push_front(&ll, (void *)0xDEAD2222);
  mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD2222);
  mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_len(&ll) == 2);

  mzp_ll_push_front(&ll, (void *)0xDEAD1111);
  mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD1111);
  mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_len(&ll) == 3);
}

void test_mzp_ll_push_back(void) {
  MZP_MEM_ALLOCATOR(ll_allocator, mzp_ll_node, 3);

  mzp_ll ll = mzp_ll_new(&ll_allocator);
  mzp_ll_push_back(&ll, (void *)0xDEAD3333);
  mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_len(&ll) == 1);

  mzp_ll_push_back(&ll, (void *)0xDEAD2222);
  mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD2222);
  mzp_assert(mzp_ll_len(&ll) == 2);

  mzp_ll_push_back(&ll, (void *)0xDEAD1111);
  mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD3333);
  mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD1111);
  mzp_assert(mzp_ll_len(&ll) == 3);
}

void test_mzp_ll_pop_front(void) {
  MZP_MEM_ALLOCATOR(ll_allocator, mzp_ll_node, 3);

  mzp_ll ll = mzp_ll_new(&ll_allocator);
  for (u32 i = 0; i < 2; ++i) {
    mzp_ll_push_front(&ll, (void *)0xDEAD3333);
    mzp_ll_push_front(&ll, (void *)0xDEAD2222);
    mzp_ll_push_front(&ll, (void *)0xDEAD1111);
    mzp_ll_pop_front(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD2222);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
    mzp_assert(mzp_ll_len(&ll) == 2);

    mzp_ll_pop_front(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD3333);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
    mzp_assert(mzp_ll_len(&ll) == 1);

    mzp_ll_pop_front(&ll);
    mzp_assert(mzp_ll_len(&ll) == 0);

    mzp_ll_push_back(&ll, (void *)0xDEAD1111);
    mzp_ll_push_back(&ll, (void *)0xDEAD2222);
    mzp_ll_push_back(&ll, (void *)0xDEAD3333);
    mzp_ll_pop_front(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD2222);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
    mzp_assert(mzp_ll_len(&ll) == 2);

    mzp_ll_pop_front(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD3333);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD3333);
    mzp_assert(mzp_ll_len(&ll) == 1);

    mzp_ll_pop_front(&ll);
    mzp_assert(mzp_ll_len(&ll) == 0);
  }
}

void test_mzp_ll_pop_back(void) {
  MZP_MEM_ALLOCATOR(ll_allocator, mzp_ll_node, 3);

  mzp_ll ll = mzp_ll_new(&ll_allocator);
  for (u32 i = 0; i < 2; ++i) {
    mzp_ll_push_front(&ll, (void *)0xDEAD3333);
    mzp_ll_push_front(&ll, (void *)0xDEAD2222);
    mzp_ll_push_front(&ll, (void *)0xDEAD1111);
    mzp_ll_pop_back(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD1111);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD2222);
    mzp_assert(mzp_ll_len(&ll) == 2);

    mzp_ll_pop_back(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD1111);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD1111);
    mzp_assert(mzp_ll_len(&ll) == 1);

    mzp_ll_pop_back(&ll);
    mzp_assert(mzp_ll_len(&ll) == 0);

    mzp_ll_push_back(&ll, (void *)0xDEAD1111);
    mzp_ll_push_back(&ll, (void *)0xDEAD2222);
    mzp_ll_push_back(&ll, (void *)0xDEAD3333);
    mzp_ll_pop_back(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD1111);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD2222);
    mzp_assert(mzp_ll_len(&ll) == 2);

    mzp_ll_pop_back(&ll);
    mzp_assert(mzp_ll_peek_front(&ll) == (void *)0xDEAD1111);
    mzp_assert(mzp_ll_peek_back(&ll) == (void *)0xDEAD1111);
    mzp_assert(mzp_ll_len(&ll) == 1);

    mzp_ll_pop_back(&ll);
    mzp_assert(mzp_ll_len(&ll) == 0);
  }
}

void test_mzp_ll(void) {
  test_mzp_ll_init();
  test_mzp_ll_new();

  test_mzp_ll_push_front();
  test_mzp_ll_push_back();

  test_mzp_ll_pop_front();
  test_mzp_ll_pop_back();
}

int main(int argc, char *argv[]) {
  test_mzp_ll();
  return 0;
}
