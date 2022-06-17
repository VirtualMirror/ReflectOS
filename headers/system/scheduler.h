#ifndef __TASK__SCHEDULER__
#define __TASK__SCHEDULER__


#define MAX_TASKS 50


void init_scheduler();
void add_task_to_scheduler(const char *, const char *, unsigned int);
void remove_task_from_scheduler(unsigned int);
void reshift_scheduler();
unsigned int check_for_empty_scheduler();


#endif