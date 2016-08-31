#ifndef EMEMORY_H
#define EMEMORY_H
// https://github.com/LeFauve/pebble_memory_tools


#include <pebble.h>

// Allocate a memory block at the bottom of the available heap
// (may fail if the heap is already fragmented; if so it will just behave like regular malloc() )
extern void* malloc_low(size_t s);

#endif