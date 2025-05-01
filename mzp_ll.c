#include "mzp_ll.h"
#include "mzp_assert.h"

mzp_ll mzp_ll_new(mzp_mem_allocator *allocator) {
  mzp_ll ll;
  mzp_ll_init(&ll, allocator);
  return ll;
}

void mzp_ll_init(mzp_ll *ll, mzp_mem_allocator *allocator) {
  ll->head = NULL;
  ll->allocator = allocator;
  ll->len = 0;
}

u32 mzp_ll_len(mzp_ll *ll) { return ll->len; }

void *mzp_ll_peek_front(mzp_ll *ll) {
  mzp_assert(mzp_ll_len(ll) != 0);
  return ll->head->data;
}

void *mzp_ll_peek_back(mzp_ll *ll) {
  mzp_assert(mzp_ll_len(ll) != 0);
  mzp_ll_node *curr = ll->head;
  while (curr->next) {
    curr = curr->next;
  }
  return curr->data;
}

void mzp_ll_push_front(mzp_ll *ll, void *data) {
  mzp_ll_node *node = mzp_mem_alloc(ll->allocator);
  node->data = data;
  node->next = ll->head;

  ll->head = node;
  ++(ll->len);
}

void *mzp_ll_pop_front(mzp_ll *ll) {
  mzp_ll_node *node = ll->head;
  void *data = node->data;
  ll->head = node->next;
  mzp_mem_dealloc(ll->allocator, node);
  --(ll->len);
  return data;
}

void mzp_ll_push_back(mzp_ll *ll, void *data) {
  if (mzp_ll_len(ll) == 0) {
    mzp_ll_push_front(ll, data);
    return;
  }

  mzp_ll_node *node = mzp_mem_alloc(ll->allocator);
  node->data = data;
  node->next = NULL;

  mzp_ll_node *curr = ll->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = node;
  ++(ll->len);
}

void *mzp_ll_pop_back(mzp_ll *ll) {
  if (mzp_ll_len(ll) == 1) {
    return mzp_ll_pop_front(ll);
  }

  mzp_ll_node *curr = ll->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  mzp_ll_node *node = curr->next;
  void *data = node->data;
  curr->next = curr->next->next;
  mzp_mem_dealloc(ll->allocator, node);
  --(ll->len);
  return data;
}
