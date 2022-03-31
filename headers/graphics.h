#ifndef __GRAPHICS__BUFFER__
#define __GRAPHICS__BUFFER__


void graphics_init();
void draw_pixel(int, int, unsigned char);
void draw_char(unsigned char, int, int, unsigned char);
void draw_string(int, int, char *, unsigned char);
void draw_rect(int, int, int, int, unsigned char, int);
void draw_circle(int, int, int, unsigned, int);
void draw_line(int, int, int, int, unsigned char);


#endif