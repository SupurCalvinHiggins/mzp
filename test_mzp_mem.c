#include "mzp_assert.h"
#include "mzp_mem.h"
#include <stdalign.h>

typedef struct {
  u32 a;
  alignas(256) u8 b[10];
} tstruct;

MZP_MEM_ALLOCATOR(allocator_u8, u8, 3);
MZP_MEM_ALLOCATOR(allocator_u32, u32, 2);
MZP_MEM_ALLOCATOR(allocator_tstruct, tstruct, 2);

void test_mzp_mem_allocator_u8(void) {
  for (int i = 0; i < 2; ++i) {
    u8 *b1 = mzp_mem_alloc(&allocator_u8);
    u8 *b2 = mzp_mem_alloc(&allocator_u8);
    u8 *b3 = mzp_mem_alloc(&allocator_u8);
    *b1 = 0x11;
    *b2 = 0x22;
    *b3 = 0x33;
    mzp_assert(*b1 == 0x11);
    mzp_assert(*b2 == 0x22);
    mzp_assert(*b3 == 0x33);
    mzp_mem_dealloc(&allocator_u8, b1);
    mzp_mem_dealloc(&allocator_u8, b2);
    mzp_mem_dealloc(&allocator_u8, b3);
  }
}

void test_mzp_mem_allocator_u32(void) {
  for (int i = 0; i < 2; ++i) {
    u32 *b1 = mzp_mem_alloc(&allocator_u32);
    u32 *b2 = mzp_mem_alloc(&allocator_u32);
    *b1 = 0x11111111;
    *b2 = 0x22222222;
    mzp_assert(*b1 == 0x11111111);
    mzp_assert(*b2 == 0x22222222);
    mzp_mem_dealloc(&allocator_u32, b1);
    mzp_mem_dealloc(&allocator_u32, b2);
  }
}

void test_mzp_mem_allocator_tstruct(void) {
  for (int i = 0; i < 2; ++i) {
    tstruct *b1 = mzp_mem_alloc(&allocator_tstruct);
    tstruct *b2 = mzp_mem_alloc(&allocator_tstruct);
    b1->a = 0x11111111;
    b2->a = 0x22222222;
    for (int i = 0; i < 10; ++i) {
      b1->b[i] = 0x33;
      b2->b[i] = 0x44;
    }
    mzp_assert(b1->a == 0x11111111);
    mzp_assert(b2->a == 0x22222222);
    for (int i = 0; i < 10; ++i) {
      mzp_assert(b1->b[i] == 0x33);
      mzp_assert(b2->b[i] == 0x44);
    }
    mzp_assert(((uptr)b1->b & 0xFF) == 0);
    mzp_assert(((uptr)b2->b & 0xFF) == 0);
    mzp_mem_dealloc(&allocator_tstruct, b1);
    mzp_mem_dealloc(&allocator_tstruct, b2);
  }
}

void test_mzp_mem(void) {
  test_mzp_mem_allocator_u8();
  test_mzp_mem_allocator_u32();
  test_mzp_mem_allocator_tstruct();
}

int main(int argc, char *argv[]) {
  test_mzp_mem();
  return 0;
}
