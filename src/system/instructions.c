#include "system/instructions.h"
#include "system/memory.h"
#include "io/io.h"


/**
 * @brief Functie voor het optellen van een waarde
 * 
 * @param value 
 * @return int 
 */
int instr_increment(int *value)
{
    return value++;
}


/**
 * @brief Functie voor het aftrekken van een waarde
 * 
 * @param value 
 * @return int 
 */
int instr_decrement(int *value)
{
    return value--;
}


/**
 * @brief Functie voor het ophalen van data uit het geheugen
 * 
 * @param address 
 * @param p_id
 * @return unsigned int 
 */
int load(unsigned long address, unsigned int p_id)
{
    
}


/**
 * @brief Functie voor het opslaan van data in het geheugen
 * 
 * @param address 
 * @param data 
 * @param p_id
 */
void store(unsigned long address, int data, unsigned int type, unsigned int p_id)
{
    memory_push_with_process_id(address, data, type, p_id);
}