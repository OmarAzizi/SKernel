#include "process.h"
#include "heap.h"

void process_init() {
    process_count = 0;
    curr_pid = 0;
}

process_t* create_process(int *base_address) {
    process_t *process = kalloc(sizeof(process_t));

    process->pid = curr_pid++;
    
    process->context.eax = 0;
    process->context.ebx = 0;
    process->context.ecx = 0;
    process->context.edx = 0;
    process->context.esp = 0;
    process->context.ebp = 0;
    process->context.esi = 0;
    process->context.edi = 0;
    process->context.eip = base_address;

    process->state = READY; // process put into ready state
    process->base_address = base_address;

    processes[process->pid] = process;
    ++process_count;

    return process;
}
