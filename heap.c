#include "heap.h"

void heap_init() { base_heap = 0x100000; }

int kalloc(int bytes) {
    unsigned int new_object_address = base_heap;
    base_heap += bytes;
    return new_object_address;
}
