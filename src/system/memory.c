#include "system/memory.h"
#include "graphics/graphics.h"
#include "io/io.h"


#define VIDEO_MEMORY_LOCATION_START     0x10000000
#define VIDEO_MEMORY_LOCATION_END       0x20000000
#define SYSTEM_MEMORY_LOCATION_START    0x20000001
#define SYSTEM_MEMORY_LOCATION_END      0x40000000

#define MAX_MEMORY_ALLOCATION           30



/**
 * @brief Structure voor gegevens van geheugen
 * 
 */
typedef struct 
{
    unsigned long address;
    int size;
} memory_info;


/**
 * @brief Functie voor het vinden en zetten van een plekje in het geheugen
 * 
 * @param size 
 * @return unsigned long 
 */
unsigned long memory_find(unsigned long size)
{
    int i;
    unsigned long start, end, temp;

    start = SYSTEM_MEMORY_LOCATION_START;
    while (mmio_read(start) != 0) start++;

    temp = start;
    for (i = 0; i < size; i++) {
        temp++;

        if (temp == SYSTEM_MEMORY_LOCATION_END) {
            temp--;
            break;
        }
    }
    end = temp;

    return start;
}


/**
 * @brief Functie voor het zetten van memory
 * 
 * @param address 
 * @param value 
 * @param size 
 */
void memory_set(unsigned long *address, char *value, unsigned int size)
{
    int i;
    unsigned long a = &address;

    if (a <= SYSTEM_MEMORY_LOCATION_START || a >= SYSTEM_MEMORY_LOCATION_END) {
        draw_string(100, 100, "Error: Geheugen valt buiten systeem adres.", 0x0F, 3);
        return;
    }

    for (i = 0; i < size; i++) {
        *((unsigned long*)(address + i)) = value[i];
    }
}


/**
 * @brief Functie voor het overkopieren van geheugen
 * 
 * @param old_address 
 * @param new_address 
 * @param size 
 */
void memory_copy(unsigned long *old_address, unsigned long *new_address, unsigned int size)
{

}


/**
 * @brief Functie voor het opschonen van geheugen
 * 
 * @param address 
 */
void memory_free(unsigned long address)
{
    unsigned int i;

    // for () {

    // }
}