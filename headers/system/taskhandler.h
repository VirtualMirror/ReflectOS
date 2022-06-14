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


struct TaskHandle *task_create(unsigned int);


#endif