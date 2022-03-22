#ifndef __GRAPHICS__BUFFER__
#define __GRAPHICS__BUFFER__


void init_graphics();
void draw_pixel(int, int, unsigned char);
void draw_character(unsigned char, int, int, unsigned char);
void draw_string(int, int, char*, unsigned char);


#endif