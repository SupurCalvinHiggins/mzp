#include "mzp_mem.h"
#include "mzp_assert.h"
#include "mzp_int.h"

#define mzp_mem_allocator_assert_ok(allocator)                                 \
  {                                                                            \
    mzp_assert(allocator != NULL);                                             \
    mzp_assert(allocator->blocks_len > 0);                                     \
    mzp_assert(allocator->block_size > 0);                                     \
    mzp_assert(allocator->free_stack_len <= allocator->blocks_len);            \
  }

#define mzp_mem_free_assert_ok(allocator, free)                                \
  {                                                                            \
    mzp_mem_allocator_assert_ok(allocator);                                    \
    mzp_assert(free < allocator->blocks_len);                                  \
  }

#define mzp_mem_data_assert_ok(allocator, data)                                \
  {                                                                            \
    mzp_mem_allocator_assert_ok(allocator);                                    \
    mzp_assert(data >= allocator->blocks);                                     \
    mzp_assert((data - allocator->blocks) % allocator->block_size == 0);       \
    mzp_mem_free_assert_ok(allocator, (data - allocator->blocks) /             \
                                          allocator->block_size);              \
  }

void mzp_mem_init(mzp_mem_allocator *allocator) {
  mzp_assert(allocator != NULL);
  for (u32 i = 0; i < allocator->blocks_len; ++i) {
    allocator->free_stack[i] = i;
  }
  allocator->free_stack_len = allocator->blocks_len;
  mzp_mem_allocator_assert_ok(allocator);
}

void *mzp_mem_alloc(mzp_mem_allocator *allocator) {
  if (allocator->free_stack_len == MZP_MEM_ALLOCATOR_UNINIT) {
    mzp_mem_init(allocator);
  }
  mzp_mem_allocator_assert_ok(allocator);
  mzp_assert(allocator->free_stack_len != 0);
  u32 free = allocator->free_stack[allocator->free_stack_len--];
  mzp_mem_free_assert_ok(allocator, free);
  void *data = allocator->blocks + (free * allocator->block_size);
  mzp_mem_data_assert_ok(allocator, data);
  return data;
}

void mzp_mem_dealloc(mzp_mem_allocator *allocator, void *data) {
  mzp_mem_allocator_assert_ok(allocator);
  mzp_mem_data_assert_ok(allocator, data);
  u32 free = (data - allocator->blocks) / allocator->block_size;
  mzp_mem_free_assert_ok(allocator, free);
  allocator->free_stack[++(allocator->free_stack_len)] = free;
  mzp_mem_allocator_assert_ok(allocator);
}
