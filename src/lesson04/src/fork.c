#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "printf.h"

//Adding priority parameter
int copy_process(unsigned long fn, unsigned long arg, unsigned int taskPriority)
{
	preempt_disable();
	struct task_struct *p;

	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	p->priority = taskPriority;
	p->state = TASK_RUNNING;
	p->counter = taskPriority;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
	int pid = nr_tasks++;
	task[pid] = p;

	//ADD COMMENTS HERE
	printf("\n\r Task[%d] created \r\n", pid);
	printf("\n\r Struct task allocated at 0x%08x. \r\n", p);
	printf("p->cpu_context.x19 = 0x%08. (fn)\r\n", p->cpu_context.x19);
	printf("p->cpu_context.x20 = 0x%08. (fn)\r\n", p->cpu_context.x20);
	printf("p->cpu_context.pc = 0x%08x. (ret_from_fork)\r\n", p->cpu_context.pc);
	printf("p->cpu_context.sp = 0x%08x. (rstack pointer)\r\n", p->cpu_context.sp);

	preempt_enable();
	return 0;
}
