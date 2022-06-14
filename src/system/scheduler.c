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
 * @brief Structure voor het opzetten van een taskhandle voor het uitvoeren van task instructions
 * 
 */
struct TaskHandle
{
    unsigned int handle_counter;
    char *handle;
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


extern struct Task *task_scheduler[MAX_TASKS];
unsigned short task_found = 0;
unsigned int task_counter = 0;


/**
 * @brief Functie voor het toevoegen van een opdracht aan de scheduler
 * 
 * @param title 
 * @param file 
 */
void add_task_to_scheduler(const char* title, const char *file)
{
    if (task_counter > MAX_TASKS) {
        task_counter == MAX_TASKS;
    }

    struct Task *new_task;

    new_task->title = title;
    new_task->file = file;
    new_task->position = ++task_counter;
    new_task->state = WAITING;

    task_scheduler[task_counter] = new_task;
}


/**
 * @brief Functie voor het verwijderen van opdrachten van de scheduler
 * 
 * @param task 
 */
void remove_task_from_scheduler(const char *task)
{
    int i;

    for (i = 0; i < MAX_TASKS; i++) {
        while (*task_scheduler[i]->file == *task) {
            task_scheduler->file++;
            task++;
        }
    }
}


/**
 * @brief Functie voor het zoeken en verwijderen van afgeronde taken
 * 
 */
void check_scheduler_for_completed_tasks()
{
    int i;

    for (i = 0; i < MAX_TASKS; i++) {
        if (task_scheduler[i]->state == SUCCESS) {
            remove_task_from_scheduler(task_scheduler[i]->file);
        }
    }
}


/**
 * @brief Functie voor het shiften van de taken naar voren in de scheduler
 * 
 */
void if_task_completed_shift_scheduler()
{
    if (task_scheduler[0] == 0) {
        struct task *temp;
    }
}


/**
 * @brief Functie voor het tijdelijk stoppen van een opdracht in de scheduler
 * 
 * @param task 
 * @param position 
 */
void task_suspend(const char *task, unsigned int position)
{
    
}


/**
 * @brief Functie voor het definitief stoppen van een opdracht in de scheduler
 * 
 * @param task 
 * @param position 
 */
void task_stopped(const char *task, unsigned int position)
{

}