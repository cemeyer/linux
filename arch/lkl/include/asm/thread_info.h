#ifndef _ASM_LKL_THREAD_INFO_H
#define _ASM_LKL_THREAD_INFO_H

#define THREAD_SIZE	       (4096)

#ifndef __ASSEMBLY__
#include <asm/types.h>
#include <asm/processor.h>

typedef struct {
	unsigned long seg;
} mm_segment_t;

struct thread_exit_info {
	bool dead;
	void *sched_sem;
};

struct thread_info {
	struct task_struct *task;
	unsigned long flags;
	int preempt_count;
	mm_segment_t addr_limit;
	void *sched_sem;
	struct thread_exit_info *exit_info;
	struct task_struct *prev_sched;
	unsigned long stackend;
};

#define INIT_THREAD_INFO(tsk)				\
{							\
	.task		= &tsk,				\
	.preempt_count	= INIT_PREEMPT_COUNT,		\
	.flags		= 0,				\
	.addr_limit	= KERNEL_DS,			\
}

#define init_thread_info	(init_thread_union.thread_info)
#define init_stack		(init_thread_union.stack)

/* how to get the thread information struct from C */
extern struct thread_info *_current_thread_info;
static inline struct thread_info *current_thread_info(void)
{
	return _current_thread_info;
}

/* thread information allocation */
struct thread_info *alloc_thread_info_node(struct task_struct *, int node);
void free_thread_info(struct thread_info *);

int threads_init(void);
void threads_cleanup(void);

#define TIF_SYSCALL_TRACE		0
#define TIF_NOTIFY_RESUME		1
#define TIF_SIGPENDING			2
#define TIF_NEED_RESCHED		3
#define TIF_RESTORE_SIGMASK		4
#define TIF_MEMDIE			5
#define TIF_NOHZ			6

#define __HAVE_THREAD_FUNCTIONS

#define task_thread_info(task)	((struct thread_info *)(task)->stack)
#define task_stack_page(task)	((task)->stack)

/*
 * Nothing to do here. The only new tasks created are kernel threads that have a
 * predefined starting point thus no stack copy is required as for regular
 * forked tasks.
 */
static inline void setup_thread_stack(struct task_struct *p,
				      struct task_struct *org)
{
}

#define end_of_stack(p) (&task_thread_info(p)->stackend)

#endif /* __ASSEMBLY__ */

#endif
