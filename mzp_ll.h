#pragma once

#include "mzp_mem.h"

typedef struct mzp_ll_node {
  void *data;
  struct mzp_ll_node *next;
} mzp_ll_node;

typedef struct mzp_ll {
  mzp_mem_allocator *allocator;
  u32 len;
  struct mzp_ll_node *head;
} mzp_ll;

mzp_ll mzp_ll_new(mzp_mem_allocator *allocator);
void mzp_ll_init(mzp_ll *ll, mzp_mem_allocator *allocator);

u32 mzp_ll_len(mzp_ll *ll);

void mzp_ll_push_front(mzp_ll *ll, void *data);
void *mzp_ll_pop_front(mzp_ll *ll);

void mzp_ll_push_back(mzp_ll *ll, void *data);
void *mzp_ll_pop_back(mzp_ll *ll);
