# SKernel
## x86 32-bit operating system kernel build with C

This is my first experience into the world of low-level development and systems programming in general, with a specific focus on kernel development. It is named SKernel, short for 'Simple Kernel,' because it is truly simple.

Some of the features this kernel provides include:

* Process Management & Multitasking
* Memory Management, including Paging
* A basic run-time heap
* A Simple Filesystem
* Interrupts

## SKernel Process Management
To manage processes and implement multitasking, I chose preemptive scheduling. The algorithm in action is Round-Robin (RR), which runs whenever the system timer goes off via system interrupt 32 isr_32 (You can check [idt.asm](https://github.com/OmarAzizi/SKernel/blob/main/idt.asm) to see it) which calls the actual scheduler implemented in [scheduler.c](https://github.com/OmarAzizi/SKernel/blob/main/scheduler.c) and performs context switching with the help of embedded assembly in C.

## SKernel Memory Management
For memory management and protection, I opted for the paging technique to protect processes and kernel memory spaces from being accessed by other processes running in memory. I implemented page frames and page tables. The paging mode used in SKernel is the 32-bit [PAE Paging](https://learn.microsoft.com/en-us/previous-versions/windows/it-pro/windows-server-2003/cc736309(v=ws.10)?redirectedfrom=MSDN).

## SKernel Filesystem
For the SKernel filesystem, I implemented a straightforward approach using a linked list structure to manage files. There base block has a head that points to the first file added onto the filesystem and a tail that points to the last one added. While this isn't the most efficient approach for a filesystem, it serves well for my learning purposes.

