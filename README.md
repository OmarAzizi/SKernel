# SKernel
## x86 32-bit operating system kernel build with C

This is my first taste in the world of low-level development & systems programming in general and kernel develpment to be specific.
It is called SKernel as a short for 'Simple Kernel', because it is a really simple.

Some of what I implemented into this kernel includes the follwoing:

* Process Management & Multitasking
* Memory Management such as Paging
* A really simple run-time heap
* A Simple Filesystem
* Interrupts

## SKernel Process Management
In order to manage processes & implement multitasking I decided to go with a preemptive scheduling. The algorithm in action is 
Round-Robin (RR) that runs and whenever the system timer goes off via system interrupt 32 isr_32, (check [idt.asm](https://github.com/OmarAzizi/SKernel/blob/main/idt.asm) 
which calles the actual scheduler I implemented in and does context switching with the help of embedded assembly in C [scheduler.c](https://github.com/OmarAzizi/SKernel/blob/main/scheduler.c).


## SKernel Memory Management
For memory management & protection I rolled with the paging technique (A classic one huh?) so I can protect the processes & kernel
memory spaces from getting accessed by other prcoesses running in memory. So I had to implement page frames & page tables. The paging
mode I used in SKernel is the 32-bit (PAE Paging)[https://learn.microsoft.com/en-us/previous-versions/windows/it-pro/windows-server-2003/cc736309(v=ws.10)?redirectedfrom=MSDN].

