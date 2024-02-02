#ifndef PROCESS_H
#define PROCESS_H

typedef enum process_state {READY, RUNNING} process_state_t;

/* 
    This structure is intended to store snapshots of the 
    x86 registers used by a process
*/
typedef struct process_context {
    int eax, ecx, edx, ebx, esp, ebp, esi, edi, eip;
} process_context_t;

/*
    This structure represents a Process Control Block (PCB) 
    which will be an entry in the processes table
*/
typedef struct process {
    int pid;
    process_context_t context;
    process_state_t state;
    int *base_address; // address of the process code starting point
} process_t;

process_t *processes[15];
int process_count, curr_pid;

void process_init(); // called by the kernel when it starts
process_t* create_process(int *);
/*
    parameters of create_process:
    1- Pointer to the base address of the process
    2- Pointer to the process control block
*/

#endif
