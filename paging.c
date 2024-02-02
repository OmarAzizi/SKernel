#include "paging.h"
#include "heap.h"

int create_page_entry(int base_address, char present, char writable, 
        char privilege_level, char cache_enabled, char write_through_cahce, 
        char accessed, char page_size, char dirty) {
 
    int entry = 0;

    entry |= present;
    entry |= writable << 1;
    entry |= privilege_level << 2;
    entry |= write_through_cahce << 3;
    entry |= cache_enabled << 4;
    entry |= accessed << 5;
    entry |= dirty << 6;
    entry |= page_size << 7;

    return base_address | entry;

}

void paging_init() {
    unsigned int curr_page_frame = 0;
    page_directory = kalloc(4 * 1024);

    for (int currPDE = 0; currPDE < PDE_NUM; ++currPDE) {
        unsigned *pageTable = kalloc(PTE_NUM * 4);

        for (int currPTE = 0; currPTE < PTE_NUM; ++currPTE, ++curr_page_frame) 
            pageTable[currPTE] = create_page_entry(curr_page_frame * 4096, 1, 0, 0, 1, 1, 0, 0, 0);

        page_directory[currPDE] = create_page_entry(pageTable, 1, 0, 0, 1, 1, 0, 0, 0); 
    }

    load_page_directory();
    enable_paging();
}
