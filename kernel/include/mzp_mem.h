#pragma once

#include "mzp_int.h"

typedef struct {
  void *blocks;
  u32 blocks_len;
  u32 block_size;
  u32 *free_stack;
  u32 free_stack_len;
} mzp_mem_allocator;

#define MZP_MEM_ALLOCATOR_UNINIT 0xDEADAFAF

#define MZP_MEM_ALLOCATOR(allocator_name, type, len)                           \
  u32 allocator_name##_free_stack[len];                                        \
  type allocator_name##_blocks[len];                                           \
  mzp_mem_allocator allocator_name = {                                         \
      .blocks = (void *)allocator_name##_blocks,                               \
      .blocks_len = len,                                                       \
      .block_size = sizeof(type),                                              \
      .free_stack = allocator_name##_free_stack,                               \
      .free_stack_len = MZP_MEM_ALLOCATOR_UNINIT,                              \
  };

void mzp_mem_init(mzp_mem_allocator *allocator);
void *mzp_mem_alloc(mzp_mem_allocator *allocator);
void mzp_mem_dealloc(mzp_mem_allocator *allocator, void *block);
