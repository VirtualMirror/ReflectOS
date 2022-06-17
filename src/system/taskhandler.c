#include "system/taskhandler.h"
#include "system/memory.h"


/**
 * @brief Functie voor het creeren van een task
 * 
 * @param p_id 
 * @return struct TaskHandle* 
 */
struct TaskHandle task_handle_create(unsigned int p_id)
{
    if (p_id < 0) {
        return;
    }

    unsigned int i;
    struct TaskHandle task;

    task.handle_counter = 0;
    task.max_handle = count_process_by_process_id(p_id);
    task.handle = 0;

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
struct TaskHandle task_handle_update(unsigned int handle_counter, unsigned int max_handle, unsigned int *handle)
{
    struct TaskHandle task;

    task.handle_counter = handle_counter;
    task.max_handle = max_handle;

    return task;
}


/**
 * @brief Functie voor het toevoegen van een taak aan de handle van de taskhandle
 * 
 * @param p_id
 */
unsigned int add_handle_to_taskhandle(unsigned int p_id)
{
    unsigned int handle_array[MAX_HANDLES_PER_PROCESS];
    unsigned int i;
    struct MemoryBlock b; 

    for (i = 0; i < 50; i++) {
        b = memory_load_first_block_by_process_id(p_id);
        handle_array[i] = b.address;
    }
   
    return handle_array;
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