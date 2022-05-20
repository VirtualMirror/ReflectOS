#include "system/memory.h"
#include "graphics/graphics.h"
#include "io/io.h"

#define MAX_MEMORY_ALLOCATION           30
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


/**
 * @brief Structure voor het opslaan van informatie over een pixel van het scherm
 * 
 */
struct Pixel 
{
    int x;
    int y;
    unsigned long address;
    unsigned char oldcolor;
    unsigned char curcolor;
};


struct MemoryBlock *memory_array[MAX_MEMORY_ALLOCATION];
struct MemoryBlock *stack[MAX_STACK_ALLOCATION];
struct Pixel *screen_buffer[1920][1080];
unsigned int sp = 0;
unsigned int pc = 0;


/**
 * @brief Functie voor het Duwen van data in het geheugen
 * 
 * @param variable 
 * @param instruction 
 */
void memory_push(unsigned int variable, unsigned long instruction)
{
    unsigned int i;
    struct MemoryBlock *new_block; 

    new_block->process_id = pc;
    new_block->address = 0x0;
    new_block->variable_name = variable;
    new_block->data = instruction;

    for (unsigned i; i < MAX_MEMORY_ALLOCATION; i++) {
        if (new_block->process_id == 0 && new_block->variable_name == "") {
            break;
        }
    }

    memory_array[i] = new_block;
}


/**
 * @brief Functie voor het verwijderen van een block uit het geheugen
 * 
 * @param position 
 * @return struct Memory_block* 
 */
struct MemoryBlock *memory_pop(unsigned int position)
{
    if (position > MAX_MEMORY_ALLOCATION) {
        return;
    }

    struct MemoryBlock *t = &memory_array[position];

    memory_array[position]->process_id = 0;
    memory_array[position]->address = 0x0;
    memory_array[position]->type = 0;
    memory_array[position]->variable_name = "";
    memory_array[position]->data = 0;

    return t;
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