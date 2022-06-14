#include "system/memory.h"
#include "graphics/graphics.h"
#include "io/io.h"
#include "system/instructions.h"
#include "system/taskhandler.h"


#define MAX_MEMORY_ALLOCATION           50
#define MAX_STACK_ALLOCATION            30


/**
 * @brief Structure voor het opslaan van een memory block
 * 
 */
struct MemoryBlock 
{
    unsigned int process_id;
    unsigned int type;
    unsigned char *variable_name;
    unsigned long address;
    unsigned long data;
};


volatile struct MemoryBlock *memory_array[MAX_MEMORY_ALLOCATION];
volatile struct MemoryBlock *stack[MAX_STACK_ALLOCATION];
volatile struct Pixel *screen_buffer[SCREEN_WIDTH][SCREEN_HEIGHT];
unsigned int sp = 0;                                            // Stack Pointer
unsigned int pi = 0;                                            // Process index
unsigned int pc = 0;                                            // Program counter


/**
 * @brief Functie voor het Duwen van data in het geheugen
 * 
 * @param variable 
 * @param instruction 
 */
void memory_push(unsigned int variable, unsigned long instruction, unsigned int type)
{
    if (variable == 0) {
        return;
    }
    if (type == 0) {
        return;
    } 

    unsigned int i;
    struct MemoryBlock *new_block; 

    new_block->process_id = pi;
    new_block->address = 0x0;
    new_block->variable_name = variable;
    new_block->data = instruction;
    new_block->type = type;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i]->process_id == 0 && memory_array[i]->variable_name == "") {
            break;
        }
    }

    memory_array[i] = new_block;
}


/**
 * @brief Functie voor het toevoegen van een block aan het geheugen met dezelfde process id
 * 
 * @param variable 
 * @param instruction 
 * @param p_id
 */
void memory_push_with_process_id(unsigned int variable, unsigned long instruction, unsigned int type, unsigned int p_id)
{
    if (variable == 0) {
        return;
    }
    if (type == 0) {
        return;
    } 

    unsigned int i;
    struct MemoryBlock *new_block;

    new_block->process_id = p_id;
    new_block->address = 0x0;
    new_block->variable_name = variable;
    new_block->data = instruction;
    new_block->type = type;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i]->process_id == 0 && memory_array[i]->variable_name == "") {
            break;
        }
    }

    memory_array[i] = new_block;
}


/**
 * @brief Functie voor het ophalen van een geheugenblock uit het geheugen
 * 
 * @param p_id 
 * @param variabele
 * @return struct MemoryBlock* 
 */
struct MemoryBlock *memory_load_with_process_id(unsigned int p_id, unsigned int variabele)
{
    unsigned int i;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i]->process_id == p_id && memory_array[i]->variable_name == variabele) {
            break;
        } else {
            return 0;
        }
    }

    return memory_array[i];
}


/**
 * @brief Functie voor het verwijderen van een block uit het geheugen
 * 
 * @param position 
 * @return struct Memory_block* 
 */
struct MemoryBlock *memory_free(unsigned int position)
{
    if (position > MAX_MEMORY_ALLOCATION) {
        return;
    }

    struct MemoryBlock **t = &memory_array[position];

    memory_array[position]->process_id = 0;
    memory_array[position]->address = 0x0;
    memory_array[position]->type = 0;
    memory_array[position]->variable_name = "";
    memory_array[position]->data = 0;

    return t;
}


/**
 * @brief Functie voor het tellen van het aantal processen in het geheugen bij een bepaald process id
 * 
 * @param p_id 
 * @return unsigned int 
 */
unsigned int count_process_by_process_id(unsigned int p_id)
{
    if (p_id < 0) {
        return;
    }

    unsigned int counter;
    unsigned int i;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i]->process_id == p_id) {
            counter++;
        }
    }

    return counter;
}


/**
 * @brief Functie voor het 
 * 
 * @param variable 
 * @param instruction 
 */
void stack_push(unsigned int variable, unsigned long instruction)
{
    struct MemoryBlock *new_block;

    if (sp <= MAX_STACK_ALLOCATION) {
        stack[++sp] = new_block;
    } else {
        sp = sp;
    }
}


/**
 * @brief Functie voor het halen van een block van de stack
 * 
 * @return struct MemoryBlock* 
 */
struct MemoryBlock *stack_pop()
{
    return stack[--sp];
}


/**
 * @brief Functie voor het zetten van een pixel in de buffer
 * 
 * @param x 
 * @param y 
 * @param attribute 
 */
void pixel_buffer_set(unsigned int x, unsigned int y, unsigned int address, unsigned char attribute)
{
    if (x > SCREEN_WIDTH || y > SCREEN_HEIGHT) {
        return;
    }

    struct Pixel *new_pixel;

    new_pixel->x = x;
    new_pixel->y = y;
    new_pixel->address = address;
    new_pixel->curcolor = attribute;

    screen_buffer[new_pixel->x][new_pixel->y] = new_pixel;
}


/**
 * @brief Functie voor het ophalen van een pixel uit de buffer
 * 
 * @param x 
 * @param y 
 * @return struct Pixel* 
 */
struct Pixel *pixel_buffer_get(unsigned int x, unsigned int y)
{
    return screen_buffer[x][y];
}