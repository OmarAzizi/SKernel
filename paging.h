#ifndef     PAGING_H
#define     PAGING_H

#define     PDE_NUM 3 // page directory entries
#define     PTE_NUM 1024 // page table entries

extern void load_page_directory();
extern void enable_paging();

unsigned int *page_directory;

void paging_init(); // this will be called when the kernel switch to protected mode
int create_page_entry(int, char, char, char, char, char, char, char, char);

#endif
