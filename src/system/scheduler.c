#include "system/scheduler.h"
#include "io/io.h"


/**
 * @brief Collectie met de statussen van verschillende taken
 * 
 */
enum TaskState 
{
    WAITING,
    SUCCESS,
    FAILED,
    SUSPENDED,
    RUNNING,
    STOPPED,
};


/**
 * @brief Structure voor het opbouwen van een task
 * 
 */
struct Task 
{
    char *title;
    enum TaskState state;
    unsigned int position;
    char *file;
};


extern struct Task task_scheduler[MAX_TASKS];


void add_task_to_scheduler()
{

}


/**
 * @brief Functie voor het verwijderen van opdrachten van de scheduler
 * 
 * @param task 
 */
void remove_task_from_scheduler(char *task)
{
    int i;

    for (i = 0; i < MAX_TASKS; i++) {
        if () {

        }
    }
}


void task_suspend()
{

}


void task_stopped()
{
    
}