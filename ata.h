/*
    This is the header file for the hard disk device driver we are implementing
*/

#ifndef     ATA_H
#define     ATA_H

#define     BASE_PORT   0x1F0
#define     SECTOR_SIZE 512

void wait_drive_until_ready(); // this function implements busy waiting on the disk

// uses ATA addressing scheme
void* read_disk(int);
void write_disk(int, short*);

// uses CHS addressing scheme
void* read_disk_chs(int);
void write_disk_chs(int, short*);

#endif
