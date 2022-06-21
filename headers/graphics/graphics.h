#pragma once


#ifndef __GRAPHICS__BUFFER__
#define __GRAPHICS__BUFFER__


void graphics_init();
void draw_pixel(int, int, unsigned char);
void draw_char(unsigned char, int, int, unsigned char, int);
void draw_string(int, int, char *, unsigned char, int);
void draw_rect(int, int, int, int, unsigned char, int);
void draw_circle(int, int, int, unsigned, int);
void draw_line(int, int, int, int, unsigned char);
void draw_icon(unsigned int, int, int, unsigned char, int);
void moveRect(int, int, int, int, int, int, unsigned char);
void init_screen();
void clear_screen(unsigned char attribute);
void wait_msec(unsigned int);
int strlen(const char *);
void debugstr(char *);
void debugcrlf(void);
void debugch(unsigned char);
void debughex(unsigned int);


#endif