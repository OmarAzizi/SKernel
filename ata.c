#include "ata.h"
#include "heap.h"

void *read_disk_chs(int sector) {
    dev_write(BASE_PORT + 6, 0x0a0); 
    dev_write(BASE_PORT + 2, 1); // number of sectors to read
    dev_write(BASE_PORT + 3, sector); // the sector number to read from
    dev_write(BASE_PORT + 4, 0); // lowest part of cylinder name
    dev_write(BASE_PORT + 5, 0); // highest part of cylinder name
    dev_write(BASE_PORT + 7, 0x20); // command port. read command: 0x20

    /*
        after the last dev_write call executes, the reading 
        will happen an [BASE_PORT + 7] so we need to wait
        until the writing is done
    */
    wait_drive_until_ready();

    /*
        after the reading is done we will start reading 
        read from [BASE_PORT + 7] into a buffer word by word
    */
    short* buffer = kalloc(SECTOR_SIZE); // we use a char because it's size is 2 bytes on 32-bit architechture which is the size of a word
     
    for (int currByte = 0; currByte < (SECTOR_SIZE / 2); ++currByte) 
        buffer[currByte] = dev_read(BASE_PORT);

    return buffer;   
}

void wait_drive_until_ready() {
    int status = 0;
    do {
        /* reads the device status 
         * 0 means operation completed 
         * 1 means that the device is still busy reading
        */
        status = dev_read(BASE_PORT + 7);     
    } while ((status ^ 0x80) == 128); // wait
}

/*
    The function read_disk receives a parameter named address instead of sector, that is, 
    the logical block address that the caller would like to read the data from, by using 
    bitwise operations the value of this parameter can be divided into the described 
    parts to be filled in the appropriate ports. The rest of read_disk is exactly same as read_disk_chs
*/

void* read_disk(int address) {
    dev_write(BASE_PORT + 6, ( 0x0e0 | ( (address & 0x0F000000) >> 24 ) ));
    dev_write(BASE_PORT + 2, 1); // number of sectors
    dev_write(BASE_PORT + 3, address & 0x000000FF);
    dev_write(BASE_PORT + 4, (address & 0x0000FF00) >> 8);
    dev_write(BASE_PORT + 5, (address & 0x00FF0000) >> 16);
    dev_write(BASE_PORT + 7, 0x20);

    wait_drive_until_ready();

    short* buffer = kalloc(SECTOR_SIZE); 

    for (int currByte = 0; currByte < (SECTOR_SIZE / 2); ++currByte) 
        buffer[currByte] = dev_read(BASE_PORT);

    return buffer;   
}

/*
    the following two functions are write_disk_chs and write_disk which
    receive a parameter called buffer which is a pointer to the data that 
    we would like to write to the disk.
*/

void write_disk_chs(int sector, short* buffer) {
    dev_write(BASE_PORT + 6, 0x0a0); 
    dev_write(BASE_PORT + 2, 1); // number of sectors to read
    dev_write(BASE_PORT + 3, sector); // the sector number to read from
    dev_write(BASE_PORT + 4, 0); // lowest part of cylinder name
    dev_write(BASE_PORT + 5, 0); // highest part of cylinder name
    dev_write(BASE_PORT + 7, 0x30); // command port. read command: 0x20

    wait_drive_until_ready();

    for (int currWord = 0; currWord < (SECTOR_SIZE / 2); ++currWord) 
        dev_write_word(BASE_PORT, buffer[currWord]);

    wait_drive_until_ready(); // to make sure that we won't return before the disk finishes the writing operation
}

void write_disk(int address, short* buffer) {
    dev_write(BASE_PORT + 6, ( 0x0e0 | ( (address & 0x0F000000) >> 24 ) ));
    dev_write(BASE_PORT + 2, 1);
    dev_write(BASE_PORT + 3, address & 0x000000FF);
    dev_write(BASE_PORT + 4, (address & 0x0000FF00) >> 8);
    dev_write(BASE_PORT + 5, (address & 0x00FF0000) >> 16);
    dev_write(BASE_PORT + 7, 0x30);

    wait_drive_until_ready();

    for (int currWord = 0; currWord < (SECTOR_SIZE / 2); ++currWord) 
        buffer[currWord] = dev_write_word(BASE_PORT, buffer[currWord]);
    
    wait_drive_until_ready();
}

