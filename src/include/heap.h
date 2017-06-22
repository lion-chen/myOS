#ifndef INCLUDE_HEAP_H_
#define INCLUDE_HEAP_H_

#include "types.h"

#define HEAP_START 0xE0000000

void init_heap();

int kmalloc_i(uint32_t len);
void *kmalloc(uint32_t len);

void kfree(int start);

void test_heap();

#endif 	// INCLUDE_HEAP_H_
