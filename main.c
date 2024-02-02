#include "filesystem.h"
#include "screen.h"
#include "process.h"
#include "scheduler.h"
#include "heap.h"
#include "paging.h"
#include "str.h"

void processA();
void processB();
void processC();
void processD();
void print_fs();

void kernel_main() {
    heap_init();
    paging_init();
    screen_init();
    process_init();
    scheduler_init();
    filesystem_init();

    print("Welcome To SKernel.");
    println();
    print("We are now in 32-bit Protected-Mode.");
    println();
    printi(777);
    println();

    /*
    create_process(&processA);
    create_process(&processB);
    create_process(&processC);
    create_process(&processD);
    */

    char* data = kalloc(512);
	strcpy(data, "The content of the first file on SKernel filesystem");	
	create_file("first_file", data);
	
	print_fs();

    print(read_file("first_file"));

	while(1);
}

void interrupt_handler(int interrupt_number) {
    print("Interrupt Received ");
	printi(interrupt_number);
	println();
}

void processA() {
    print("Process A, ");
    while (1) 
        asm("mov $300, %eax");
}

void processB() {
    print("Process B, ");
    while (1) 
        asm("mov $400, %eax");
}

void processC() {
    print("Process C, ");
    while (1)
        asm("mov $500, %eax");
}

void processD() {
    print("Process D, ");
    while (1)
        asm("mov $600, %eax");
}

// this function prints the run-time filesystem
void print_fs() {
    char** files = list_files();
    
    int files_number = get_files_number();
    for (int currIdx = 0; currIdx < files_number; ++currIdx) {
        print("File: ");
        print(files[currIdx]);
        println();
    }

    print("==");
    println();
}


