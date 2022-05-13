#include "graphics/screen.h"
#include "io/io.h"
#include "graphics/graphics.h"
#include "system/memory.h"


unsigned char* front_buffer;
unsigned char* back_buffer;

unsigned long offset;


/**
 * @brief Functie voor het vinden van vrije memory
 * 
 * @param size 
 * @return unsigned int 
 */
unsigned int mem_alloc(unsigned int size)
{   
    unsigned int i, *mem_loc;

    while (mmio_read(mem_loc) != 0) mem_loc++;

    return mem_loc;
}


/**
 * @brief Functie voor het zetten van waardes op een plek in het geheugen
 * 
 * @param address 
 * @param value 
 * @param length 
 */
void mem_set(unsigned long address, int value, unsigned int length)
{
    unsigned int i;

    for (i = 0; i < length; i++) {
        *((unsigned int*)(address + i)) = value;
    }
}


/**
 * @brief Functie voor het kopieren van het oude adres naar het nieuwe adres
 * 
 * @param old_address 
 * @param new_address 
 * @param value 
 * @param length 
 */
void mem_cpy(unsigned long old_address, unsigned long new_address, unsigned int length)
{
    unsigned int i;

    for (i = 0; i < length; i++) {
        *((unsigned int*)(new_address + i)) = *((unsigned int*)old_address + i);
    }
}


/**
 * @brief Setup voor display
 * 
 * @param width
 * @param height
 */
void display_init(unsigned int width, unsigned int height, int pitch)
{
    graphics_init();
    
    front_buffer = 4069;
    back_buffer = mem_alloc(height * pitch);

    
}


/**
 * @brief Functie voor het swappen van buffers
 * 
 */
void swap_buffers()
{
    *((unsigned int*)(front_buffer + offset)) = *((unsigned int*)(back_buffer)); 
}