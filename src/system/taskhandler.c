#include "system/taskhandler.h"
#include "system/memory.h"


/**
 * @brief Functie voor het creeren van een task
 * 
 * @param p_id 
 * @return struct TaskHandle* 
 */
struct TaskHandle *task_handle_create(unsigned int p_id)
{
    struct TaskHandle *task;

    task->handle_counter = 0;
    task->max_handle = count_process_by_process_id(p_id);

    return task;
}


/**
 * @brief Functie voor het updaten van een task handle
 * 
 * @param handle_counter 
 * @param max_handle 
 * @param handle 
 * @return struct TaskHandle* 
 */
struct TaskHandle *task_handle_update(unsigned int handle_counter, unsigned int max_handle, unsigned int *handle)
{
    struct TaskHandle *task;

    task->handle_counter = handle_counter;
    task->max_handle = max_handle;
    task->handle = handle;

    return task;
}


/**
 * @brief Functie voor het verwijderen van een task handle
 * 
 * @param handle 
 */
void task_handle_remove(const struct TaskHandle *handle)
{
    unsigned int address = &handle;
    *((unsigned int *)(address)) = 0;
}