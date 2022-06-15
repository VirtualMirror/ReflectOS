#ifndef __SYSTEM__TASK__HANDLER__
#define __SYSTEM__TASK__HANDLER__


#define MAX_HANDLES_PER_PROCESS 50000


/**
 * @brief Structure voor het opzetten van een taskhandle voor het uitvoeren van task instructions
 * 
 */
struct TaskHandle
{
    unsigned int handle_counter;
    unsigned int max_handle;
    unsigned int *handle;
};


struct TaskHandle *task_handle_create(unsigned int);
struct TaskHandle *task_handle_update(unsigned int, unsigned int, unsigned int *);
void task_handle_remove(const struct TaskHandle *);


#endif