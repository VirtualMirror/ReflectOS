#include "system/scheduler.h"
#include "io/io.h"
#include "system/memory.h"
#include "system/instructions.h"
#include "system/taskhandler.h"


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
    EMPTY,
};


/**
 * @brief Structure voor het opbouwen van een task
 * 
 */
struct Task 
{
    char *title;
    enum TaskState state;
    int position;
    char *file;
    struct TaskHandle handle;
};


static struct Task task_scheduler[MAX_TASKS];
unsigned short task_found = 0;
unsigned int task_counter = 0;


/**
 * @brief Functie om de scheduler te initialiseren
 * 
 */
void init_scheduler()
{
    if (task_counter != 0) {
        task_counter == 0;
    }

    unsigned int i;

    for (i = 0; i < MAX_TASKS; i++) {
        task_scheduler[i].title = "";
        task_scheduler[i].state = EMPTY;
        task_scheduler[i].position = -1;
    }
}


/**
 * @brief Functie voor het toevoegen van een opdracht aan de scheduler
 * 
 * @param title 
 * @param file 
 * @param p_id
 */
void add_task_to_scheduler(const char* title, const char *file, unsigned int p_id)
{
    if (task_counter > MAX_TASKS) {
        task_counter == MAX_TASKS;
        return;
    }

    struct Task new_task;

    new_task.title = title;
    new_task.file = file;
    new_task.position = task_counter;
    new_task.state = WAITING;
    new_task.handle = task_handle_create(p_id);

    task_scheduler[task_counter] = new_task;
    task_counter++;
}


/**
 * @brief Functie voor het verwijderen van opdrachten van de scheduler
 * 
 * @param position
 */
void remove_task_from_scheduler(unsigned int position)
{
    if (position < 0) {
        return;
    }

    unsigned int i;

    for (i = 0; i < MAX_TASKS; i++) {
        if (task_scheduler[i].position == position) {
            break;
        }
    }

    task_scheduler[i].state = EMPTY;
    task_scheduler[i].position = -1; 
    task_scheduler[i].title = "";    
}


/**
 * @brief Functie voor het zoeken en verwijderen van afgeronde taken
 * 
 */
void check_scheduler_for_completed_tasks()
{
    int i;

    for (i = 0; i < MAX_TASKS; i++) {
        if (task_scheduler[i].state == SUCCESS) {
                remove_task_from_scheduler(task_scheduler[i].position);
        }
    }
}


/**
 * @brief Functie voor het shiften van de taken naar voren in de scheduler
 * 
 */
void reshift_scheduler()
{
    unsigned int i;

    for (i = 0; i < MAX_TASKS; i++) {
        if (i+1 > MAX_TASKS) {
            return;
        } 

        if ((task_scheduler[i].state == EMPTY || task_scheduler[i].state == STOPPED) && task_scheduler[i+1].state != EMPTY) {
            struct Task temp = task_scheduler[i+1];
            task_scheduler[i] = temp;
            task_scheduler[i+1].state = EMPTY;
            task_scheduler[i+1].title = "";
            task_scheduler[i+1].file = "";
        }
    }
}


/**
 * @brief Functie voor het checken of de task scheduler leeg is of niet
 * 
 * @return unsigned int 
 */
unsigned int check_for_empty_scheduler()
{
    unsigned int i, counter;

    draw_string(600, 600, task_scheduler[0].title, 0x0f, 7);

    counter = 0;
    for (i = 0; i < MAX_TASKS; i++) {
        if (task_scheduler[i].state != EMPTY) {
            counter++;
        }
    }

    if (counter != 0) {
        return counter;
    }

    return 0;
}


/**
 * @brief Functie voor het uitvoeren van processen uit de scheduler
 * 
 */
void execute_task_from_scheduler()
{
    struct MemoryBlock b;

    execute_instruction(0, 0, 0);

    if (task_scheduler[task_counter].handle.handle_counter > task_scheduler[task_counter].handle.max_handle) {
        task_scheduler[task_counter].state = SUCCESS;
    }

    if (task_scheduler[task_counter].state == SUCCESS) {
        task_counter++;

        if (task_counter > MAX_TASKS) {
            task_counter = 0;
        }
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


/**
 * @brief Functie voor het uitvoeren van een instructie uit het geheugen
 * 
 * @param instruction
 * @param value_1
 * @param value_2
 */
void execute_instruction(const unsigned int instruction, unsigned int value_1, unsigned int value_2)
{
    switch (instruction)
    {
        case CHAR:
            
        break;
        case INT:

        break;
        case LONG:

        break;
        case SHORT:

        break;
        case FLOAT:

        break;
        case DOUBLE:

        break;
        case INCREMENT:

        break;
        case DECREMENT:

        break;
        case COMPARE:

        break;
        case ADD:

        break;
        case REMOVE:

        break;
        case LOAD:

        break;
        case STORE:

        break;
        case EQUALS:

        break;
        case NOTEQUALS:

        break;
        case LESSTHAN:

        break;
        case LESSTHANOREQUAL:

        break;
        case GREATERTHAN:

        break;
        case GREATERTHANOREQUAL:

        break;
        case MAX:

        break;
        case MIN:

        break;
        case IF:

        break;
        case ELSE:

        break;
        case ENDIF:

        break;
        case FOR:

        break;
        case ENDFOR:

        break;
        case WHILE:

        break;
        case ENDWHILE:

        break;
        case PRINT:

        break;
    }
}