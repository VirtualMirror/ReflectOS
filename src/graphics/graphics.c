#include "io/io.h"
#include "graphics/buffer.h"
#include "font/font.h"
#include "system/memory.h"


unsigned int width;
unsigned int height;
unsigned int pitch;
unsigned int is_rgb;
unsigned char *frame_buffer;
struct Pixel * p_temp;


/**
 * @brief 
 * 
 */
void graphics_init()
{
    mbox[0] = 35*4; // Length of message in bytes
    mbox[1] = MBOX_REQUEST;

    mbox[2] = MBOX_TAG_SETPHYWH; // Tag identifier
    mbox[3] = 8; // Value size in bytes
    mbox[4] = 0;
    mbox[5] = 1920; // Value(width)
    mbox[6] = 1080; // Value(height)

    mbox[7] = MBOX_TAG_SETVIRTWH;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 1920;
    mbox[11] = 1080;

    mbox[12] = MBOX_TAG_SETVIRTOFF;
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0; // Value(x)
    mbox[16] = 0; // Value(y)

    mbox[17] = MBOX_TAG_SETDEPTH;
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32; // Bits per pixel

    mbox[21] = MBOX_TAG_SETPXLORDR;
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1; // RGB

    mbox[25] = MBOX_TAG_GETFB;
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096; // FrameBufferInfo.pointer
    mbox[29] = 0;    // FrameBufferInfo.size

    mbox[30] = MBOX_TAG_GETPITCH;
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0; // Bytes per line

    mbox[34] = MBOX_TAG_LAST;

    // Check call is successful and we have a pointer with depth 32
    if (mbox_video_core_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
        mbox[28] &= 0x3FFFFFFF; // Convert GPU address to ARM address
        width = mbox[10];       // Actual physical width
        height = mbox[11];      // Actual physical height
        pitch = mbox[33];       // Number of bytes per line
        is_rgb = mbox[24];       // Pixel order
        frame_buffer = (unsigned char *)((long)mbox[28]);
    }
}


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param attribute 
 */
void draw_pixel(int x, int y, unsigned char attribute)
{
    int offs = (y * pitch) + (x * 4);
    *((unsigned int*)(frame_buffer + offs)) = vgapal[attribute & 0x0f];
    // p_temp = pixel_buffer_get(x, y);
    // pixel_buffer_set(x, y, p_temp->address, attribute);
    // *((unsigned int*)(p_temp->address)) = vgapal[attribute & 0x0f];
}


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param attribute 
 */
unsigned int get_pixel_location(int x, int y)
{
    int offs = (y * pitch) + (x * 4);
    // *((unsigned int*)(frame_buffer + offs)) = vgapal[attribute & 0x0f];
    return frame_buffer+offs;
}


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param attribute 
 */
void draw_buffer_pixel(int x, int y, unsigned char attribute)
{
    int offs = (y * pitch) + (x * 4);
}


/**
 * @brief 
 * 
 * @param x1 
 * @param x2 
 * @param y2 
 * @param attribute 
 * @param fill 
 */
void draw_rect(int x1, int y1, int x2, int y2, unsigned char attribute, int fill)
{
    int y=y1;

    while (y <= y2) {
       int x=x1;
       while (x <= x2) {
	  if ((x == x1 || x == x2) || (y == y1 || y == y2)) draw_pixel(x, y, attribute);
	  else if (fill) draw_pixel(x, y, (attribute & 0xf0) >> 4);
          x++;
       }
       y++;
    }
}


/**
 * @brief 
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @param attribute 
 */
void draw_line(int x1, int y1, int x2, int y2, unsigned char attribute)  
{  
    int dx, dy, p, x, y;

    dx = x2-x1;
    dy = y2-y1;
    x = x1;
    y = y1;
    p = 2*dy-dx;

    while (x<x2) {
       if (p >= 0) {
          draw_pixel(x,y,attribute);
          y++;
          p = p+2*dy-2*dx;
       } else {
          draw_pixel(x,y,attribute);
          p = p+2*dy;
       }
       x++;
    }
}


/**
 * @brief 
 * 
 * @param x0 
 * @param y0 
 * @param radius 
 * @param attribute 
 * @param fill 
 */
void draw_circle(int x0, int y0, int radius, unsigned char attribute, int fill)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y) {
	if (fill) {
	   draw_line(x0 - y, y0 + x, x0 + y, y0 + x, (attribute & 0xf0) >> 4);
	   draw_line(x0 - x, y0 + y, x0 + x, y0 + y, (attribute & 0xf0) >> 4);
	   draw_line(x0 - x, y0 - y, x0 + x, y0 - y, (attribute & 0xf0) >> 4);
	   draw_line(x0 - y, y0 - x, x0 + y, y0 - x, (attribute & 0xf0) >> 4);
	}

	draw_pixel(x0 - y, y0 + x, attribute);
	draw_pixel(x0 + y, y0 + x, attribute);
	draw_pixel(x0 - x, y0 + y, attribute);
    draw_pixel(x0 + x, y0 + y, attribute);
	draw_pixel(x0 - x, y0 - y, attribute);
	draw_pixel(x0 + x, y0 - y, attribute);
	draw_pixel(x0 - y, y0 - x, attribute);
	draw_pixel(x0 + y, y0 - x, attribute);

	if (err <= 0) {
	    y += 1;
	    err += 2*y + 1;
	}
 
	if (err > 0) {
	    x -= 1;
	    err -= 2*x + 1;
	}
    }
}


/**
 * @brief 
 * 
 * @param ch 
 * @param x 
 * @param y 
 * @param attribute 
 */
void draw_char(unsigned char ch, int x, int y, unsigned char attribute, int zoom)
{
    unsigned char *glyph = (unsigned char *)&font + (ch < FONT_NUMGLYPHS ? ch : 0) * FONT_BPG;

    for (int i=0;i<(FONT_HEIGHT*zoom);i++) {
        for (int j=0;j<(FONT_WIDTH*zoom);j++) {
            unsigned char mask = 1 << (j/zoom);
            unsigned char col = (*glyph & mask) ? attribute & 0x0f : (attribute & 0x00) >> 4;

            draw_pixel(x+j, y+i, col);
        }

        glyph += (i%zoom) ? 0 : FONT_BPL;
    }
}


/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param s 
 * @param attribute
 * @param zoom
 */
void draw_string(int x, int y, char *s, unsigned char attribute, int zoom)
{
    while (*s) {
       if (*s == '\r') {
          x = 0;
       } else if(*s == '\n') {
          x = 0; y += (FONT_HEIGHT * zoom);
       } else {
	  draw_char(*s, x, y, attribute, zoom);
          x += (FONT_WIDTH*zoom);
       }
       s++;
    }
}


void moveRect(int oldx, int oldy, int width, int height, int shiftx, int shifty, unsigned char attr)
{
    unsigned int newx = oldx + shiftx, newy = oldy + shifty;
    unsigned int xcount = 0, ycount = 0;
    unsigned int bitmap[width][height]; // This is very unsafe if it's too big for the stack...
    unsigned int offs;

    // Save the bitmap
    while (xcount < width) {
       while (ycount < height) {
          offs = ((oldy + ycount) * pitch) + ((oldx + xcount) * 4);

	  bitmap[xcount][ycount] = *((unsigned int*)(frame_buffer + offs));
	  ycount++;
       }
       ycount=0;
       xcount++;
    }
    // Wipe it out with background colour
    draw_rect(oldx, oldy, oldx + width, oldy + width, 0x0f, 1);
    // Draw it again
    for (int i=newx;i<newx + width;i++) {
        for (int j=newy;j<newy + height;j++) {
            offs = (j * pitch) + (i * 4);
	        *((unsigned int*)(frame_buffer + offs)) = bitmap[i-newx][j-newy];
        }
    }
}


/**
 * @brief Functie voor het opstellen van het scherm
 * 
 */
void init_screen()
{
    unsigned int i, j;

    for (i = 0; i < SCREEN_WIDTH; i++) {
        for (j = 0; j < SCREEN_HEIGHT; j++) {
            pixel_buffer_set(1920, 1080, get_pixel_location(i, j), 0x0f+20);
            p_temp = pixel_buffer_get(i, j);
            *((unsigned int*)(p_temp->address)) = vgapal[p_temp->curcolor & 0x0f];

            if (i == 1919) {
                draw_string(400, 400, "Testen", 0x0f, 9);
                p_temp = pixel_buffer_get(2, 2);
                draw_char(p_temp->x + 0x30, 400, 800, 0x0f, 9);
            }
        }
    }
}


void update_screen(int x, int y, unsigned char attribute)
{

}


/**
 * @brief 
 * 
 * @param attribute 
 */
void clear_screen(unsigned char attribute)
{
    for (unsigned short i = 0; i < SCREEN_WIDTH; i++) {
        for (unsigned short j = 0; j < SCREEN_HEIGHT; j++) {
            p_temp = pixel_buffer_get(i, j);
            
            if (p_temp == 0) {
                draw_string(400, 400, "Foutcode", 0x0f, 9);
                return;
            }

            *((unsigned int *)(p_temp->address)) = vgapal[p_temp->curcolor & 0x0f];
        }
    }
}