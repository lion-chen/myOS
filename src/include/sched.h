#ifndef INCLUDE_SCHEDULER_H_
#define INCLUDE_SCHEDULER_H_

#include "task.h"

extern struct task_struct *running_proc_head;

extern struct task_struct *wait_proc_head;

extern struct task_struct *current;

void init_sched();

void schedule();

void change_task_to(struct task_struct *next);

void switch_to(struct context *prev, struct context *next);

#endif 	// INCLUDE_SCHEDULER_H_
