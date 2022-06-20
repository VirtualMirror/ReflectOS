#include "system/memory.h"
#include "graphics/graphics.h"
#include "io/io.h"
#include "system/instructions.h"
#include "system/taskhandler.h"


#define MAX_MEMORY_ALLOCATION           150
#define MAX_STACK_ALLOCATION            30


static struct MemoryBlock memory_array[MAX_MEMORY_ALLOCATION];
volatile struct MemoryBlock stack[MAX_STACK_ALLOCATION];
static struct Pixel sb[SCREEN_WIDTH][SCREEN_HEIGHT];
unsigned int sp = 0;                                            // Stack Pointer
unsigned int pi = 0;                                            // Process index
unsigned int pc = 0;       
unsigned int mc = 0;                                     // Program counter


/**
 * @brief Functie om het geheugen systeem van het besturingssysteem op te zetten
 * 
 */
void init_memory()
{
    for (unsigned int i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        memory_array[i].address = i;
        memory_array[i].process_id = -1;
        memory_array[i].variable_name = 2;

        draw_char(memory_array[i].address+0x30, 400, 400, 0x0f, 7);
    }
}


/**
 * @brief Functie voor het Duwen van data in het geheugen
 * 
 * @param variable 
 * @param instruction 
 */
void memory_push(unsigned int variable, long data_1, long data_2, unsigned int type)
{
    if (variable == 0) {
        return;
    }
    if (type == 0) {
        return;
    } 

    unsigned int i;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i].process_id == -1) {
            break;
        }
    }

    memory_array[i].process_id = pi;
    memory_array[i].address = memory_array[i].address;
    memory_array[i].variable_name = variable;
    memory_array[i].data_1 = data_1;
    memory_array[i].data_2 = data_2;
    memory_array[i].type = type;
}


/**
 * @brief Functie voor het toevoegen van een block aan het geheugen met dezelfde process id
 * 
 * @param variable 
 * @param instruction 
 * @param p_id
 */
void memory_push_with_process_id(unsigned int variable, long data_1, long data_2, unsigned int type, unsigned int p_id)
{
    if (variable == 0) {
        return;
    }
    if (type == 0) {
        return;
    } 

    unsigned int i;
    struct MemoryBlock new_block;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i].process_id == -1) {
            break;
        }
    }

    new_block.process_id = p_id;
    new_block.address = memory_array[i].address;
    new_block.variable_name = variable;
    new_block.data_1 = data_1;
    new_block.data_2 = data_2;
    new_block.type = type;



    memory_array[i] = new_block;
}


/**
 * @brief Functie voor het laden van een geheugenblock uit het geheugen aan de hand van een adres
 * 
 * @param address 
 * @return struct MemoryBlock 
 */
struct MemoryBlock memory_load_with_address(unsigned int address)
{
    if (address <= 0) {
        return;
    }

    unsigned int i;
    struct MemoryBlock new_block;

    
}


/**
 * @brief Functie voor het ophalen van een geheugenblock uit het geheugen
 * 
 * @param p_id 
 * @param variabele
 * @return struct MemoryBlock
 */
struct MemoryBlock memory_load_with_process_id(unsigned int p_id, unsigned int variabele)
{
    unsigned int i;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i].process_id == p_id && memory_array[i].variable_name == variabele) {
            break;
        } 
    }

    return memory_array[i];
}


/**
 * @brief Functie om het eerste geheugenblok te laden van het process
 * 
 * @param p_id 
 * @return struct MemoryBlock 
 */
struct MemoryBlock memory_load_first_block_by_process_id(unsigned int p_id)
{
    unsigned int i;

    for (i = 0; i < MAX_MEMORY_ALLOCATION; i++) {
        if (memory_array[i].process_id == p_id) {
            break;
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
struct MemoryBlock memory_free(unsigned int position)
{
    if (position > MAX_MEMORY_ALLOCATION) {
        return;
    }

    struct MemoryBlock t = memory_array[position];

    memory_array[position].process_id = -1;
    memory_array[position].address = 0x0;
    memory_array[position].type = 0;
    memory_array[position].variable_name = memory_array[position].variable_name;
    memory_array[position].data_1 = 0;
    memory_array[position].data_2 = 0;

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
        if (memory_array[i].process_id == p_id) {
            counter++;
        }
    }

    return counter;
}


/**
 * @brief Show inhoud van het geheugem
 * 
 */
void show_memory_contents()
{
    if (mc < 0) {
        return;
    }

    unsigned int char_offset = 56;

    draw_string(300, 700, "Address: ", 0x0f, 7);
    draw_char(memory_array[2].variable_name+0x30, 300 + (char_offset*9), 700, 0x0f, 7);

    if (mc > MAX_MEMORY_ALLOCATION) {
        mc = 0;
    } else {
        mc++;
    }
}


/**
 * @brief Functie voor het 
 * 
 * @param variable 
 * @param instruction 
 */
void stack_push(unsigned int variable, unsigned long instruction)
{
    struct MemoryBlock new_block;

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
struct MemoryBlock stack_pop()
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

    struct Pixel new_pixel;

    new_pixel.x = x;
    new_pixel.y = y;
    new_pixel.address = address;
    new_pixel.curcolor = attribute;

    sb[new_pixel.x][new_pixel.y] = new_pixel;
}


/**
 * @brief Functie voor het ophalen van een pixel uit de buffer
 * 
 * @param x 
 * @param y 
 * @return struct Pixel* 
 */
struct Pixel pixel_buffer_get(unsigned int x, unsigned int y)
{
    return sb[x][y];
}