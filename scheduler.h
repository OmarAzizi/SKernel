#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

int next_sch_pid, curr_sch_pid; // stores the PID of the next process that will be run
process_t *next_process; // stores the PID of the current process

void scheduler_init(); // will be called when the kernel starts

process_t *get_next_process();

void scheduler(int, int, int, int, int, int, int, int, int);
/*
    This function will be called when the system timer emits it's
    interrupt. It chooses the next process to run with the help of the
    function get_next_process

    It performs context switching
 */

void run_next_process();

#endif
