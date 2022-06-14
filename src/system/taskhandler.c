#include "system/taskhandler.h"
#include "system/memory.h"


/**
 * @brief Functie voor het creeren van een task
 * 
 * @param p_id 
 * @return struct TaskHandle* 
 */
struct TaskHandle *task_create(unsigned int p_id)
{
    struct TaskHandle *task;

    task->handle_counter = 0;
    task->max_handle = count_process_by_process_id(p_id);

    return task;
}


