#ifndef HEAP_H
#define HEAP_H

/* 
    This variable contain the base address of our run-time heap 
    and we can use it to allocate memory throught the function kalloc
*/
unsigned int base_heap;

void heap_init();
int kalloc(int); // stands for Kernel Allocate
                 
#endif
