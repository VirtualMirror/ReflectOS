#ifndef __SYSTEM__MEMORY__
#define __SYSTEM__MEMORY__


#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080


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


void memory_push(unsigned int, unsigned long);
struct MemoryBlock *memory_free(unsigned int);
void stack_push(unsigned int, unsigned long);
struct MemoryBlock *stack_pop();
void pixel_buffer_set(unsigned int, unsigned int, unsigned int, unsigned char);
struct Pixel *pixel_buffer_get(unsigned int, unsigned int);


#endif  