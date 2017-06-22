#include "sched.h"
#include "heap.h"
#include "debug.h"

struct task_struct *running_proc_head = NULL;

struct task_struct *wait_proc_head = NULL;

struct task_struct *current = NULL;

void init_sched()
{
	current = (struct task_struct *)(kern_stack_top - STACK_SIZE);

	current->state = TASK_RUNNABLE;
	current->pid = now_pid++;
	current->stack = current; 	// current = low stack address
	current->mm = NULL; 	

	current->next = current;

	running_proc_head = current;
}

void schedule()
{
	if (current) {
		change_task_to(current->next);
	}
}

void change_task_to(struct task_struct *next)
{
	if (current != next) {
		struct task_struct *prev = current;
		current = next;
		switch_to(&(prev->context), &(current->context));
	}
}

