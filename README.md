# SKernel 🕸️
![C Icon](https://img.shields.io/badge/language-C-blue?style=for-the-badge&logo=c)
![Assembly Icon](https://img.shields.io/badge/x86-Assembly-green?style=for-the-badge&logo=assembly)

1. [About SKernel](#about-skernel)
2. [Features](#features) 
   - [Skernel Process Management](#skernel-process-management)
   - [Skernel Memory Management](#skernel-memory-management)
   - [Skernel Filesystem](#skernel-filesystem)
   - [Skernel Video/Display Mode](#skernel-video-mode)
4. [SKernel Limitations](#skernel-limitations) 
5. [Clone and Build](#clone-and-build) 
6. [Honorable Mentions](#honorable-mentions) 


## About SKernel
Skernel is a bare-bones x86 32-bit operating system kernel built with C. It is named SKernel, short for 'Simple Kernel' because it is truly simple. This is my first experience in the world of low-level development and systems programming in general, with a specific focus on kernel development, so feel free to contribute or criticize as im still learning. 
<br><br>

Some of the features this kernel provides include:

* Process Management & Multitasking
* Memory Management, including Paging
* A Simple Filesystem
* Interrupts

## Features

### SKernel Process Management
To manage processes and implement multitasking, I chose preemptive scheduling. The algorithm in action is Round-Robin (RR), which runs whenever the system timer goes off via system interrupt 32 isr_32 (You can check [idt.asm](https://github.com/OmarAzizi/SKernel/blob/main/idt.asm) to see it) which calls the actual scheduler implemented in [scheduler.c](https://github.com/OmarAzizi/SKernel/blob/main/scheduler.c) and performs context switching with the help of embedded assembly in C.

### SKernel Memory Management 
For memory management and protection, I opted for the paging technique to protect processes and kernel memory spaces from being accessed by other processes running in memory. I implemented page frames and page tables. The paging mode used in SKernel is the 32-bit [PAE Paging](https://learn.microsoft.com/en-us/previous-versions/windows/it-pro/windows-server-2003/cc736309(v=ws.10)?redirectedfrom=MSDN).

### SKernel Filesystem
For the SKernel filesystem, I implemented a straightforward approach using a linked list structure to manage files. A base block was used that has a head that points to the first file added onto the filesystem and a tail that points to the last one added. While this isn't the most efficient approach for a filesystem, it serves well for my learning purposes.

### SKernel Video Mode
For the screen mode, I utilized the [VGA Text Mode](https://wiki.osdev.org/VGA_Hardware) with 16 colors. I didn't focus extensively on this aspect of the kernel, instead I employed it primarily to display text on the screen for testing other components of the kernel. Since my main emphasis was on understanding the kernel's components, doing graphics programming did not really align with my current learning goals.

## SKernel Limitations
Some of the kernel limitations manifests themselves into the following:

* It is not intended to be a fully usable kernel, rather, its primary purpose is to try and teach myself about kernel development
* The run-time heap implemented is not a true heap, it serves as a basic way to mimic memory allocation at runtime, allowing me focus on other aspects of the kernel 
* A shell or command-line interface is not implemented
* There may be some bugs and errors in the code that I overlooked as well

## Clone and Build
You can clone the source code of this project to your local machine using:
```bash
git clone https://github.com/OmarAzizi/SKernel.git
```
<br>

The source code includes a GNU/Make Makefile so you can build the project through:
```bash
make kernel
```
Which will build the kernel source code and run it using the QEMU emulator ([Install QEMU](https://www.qemu.org/)).
<br>

You can rerun the kernel without building it again using:
```bash
make rerun-kernel
```

## Honorable Mentions
This section acknowledges and gives credit to the main resources I used while building my kernel.

* [A Journey in Creating an Operating System Kernel Book](https://539kernel.com/)
* [OSDev Wiki](https://wiki.osdev.org/Main_Page)

