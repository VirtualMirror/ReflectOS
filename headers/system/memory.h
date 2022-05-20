#ifndef __SYSTEM__MEMORY__
#define __SYSTEM__MEMORY__


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


unsigned long memory_find(unsigned long);
void memory_set(unsigned long*, char*, unsigned int);
void memory_copy();
void memory_free();


#endif  