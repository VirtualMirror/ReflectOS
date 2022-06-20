#pragma once


#ifndef __SYSTEM__MEMORY__
#define __SYSTEM__MEMORY__


#define SCREEN_WIDTH    100
#define SCREEN_HEIGHT   100


/**
 * @brief Structure voor het opslaan van een memory block
 * 
 */
#pragma pack(1)
struct MemoryBlock 
{
    int process_id;
    unsigned int type;
    unsigned int variable_name;
    unsigned long address;
    int data_1;
    int data_2;
};


/**
 * @brief Structure voor het opslaan van informatie over een pixel van het scherm
 * 
 */
#pragma pack(1)
struct Pixel 
{
    unsigned int x;
    unsigned int y;
    unsigned long address;
    unsigned char curcolor;
};

extern volatile struct Pixel *screen_buffer[SCREEN_WIDTH][SCREEN_HEIGHT];


void init_memory();
void memory_push(unsigned int, long, long, unsigned int);
void memory_push_with_process_id(unsigned int, long, long, unsigned int, unsigned int);
struct MemoryBlock memory_load_first_block_by_process_id(unsigned int);
struct MemoryBlock memory_load_with_process_id(unsigned int, unsigned int);
struct MemoryBlock memory_free(unsigned int);
unsigned int count_process_by_process_id(unsigned int);
void stack_push(unsigned int, unsigned long);
struct MemoryBlock stack_pop();
void pixel_buffer_set(unsigned int, unsigned int, unsigned int, unsigned char);
struct Pixel pixel_buffer_get(unsigned int, unsigned int);


#endif  