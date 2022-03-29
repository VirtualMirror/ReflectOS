#include "io.h"
#include "buffer.h"
#include "font.h"

#define WIDTH 1920
#define HEIGHT 1080

uint16_t width;
uint16_t height;
uint16_t pitch;
uint8_t is_rgb;
unsigned char* frame_buffer;

/**
 * @brief Functie om de graphics interface op te zetten
 */
void init_graphics()
{
    mbox[0] = 35 * 4;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = MBOX_TAG_SETPHYWH;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = WIDTH;
    mbox[6] = HEIGHT;

    mbox[7] = MBOX_TAG_SETVIRTWH;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = WIDTH;
    mbox[11] = HEIGHT;

    mbox[12] = MBOX_TAG_SETVIRTOFF;
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0;
    mbox[16] = 0;

    mbox[17] = MBOX_TAG_SETDEPTH;
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32;

    mbox[21] = MBOX_TAG_SETPXLORDR;
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1;

    mbox[25] = MBOX_TAG_GETFB;
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096;
    mbox[29] = 0;

    mbox[30] = MBOX_TAG_GETPITCH;
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0;

    mbox[34] = MBOX_TAG_LAST;

    if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
        mbox[28] &= 0x3FFFFFFF;
        width = mbox[10];
        height = mbox[11];
        pitch = mbox[33];
        is_rgb = mbox[24];
        frame_buffer = (unsigned char*)((long)mbox[28]);
    }
}

/**
 * @brief Functie voor het schrijven van een pixel naar werkgeheugen
 * @param x 
 * @param y 
 * @param attribute 
 */
void draw_pixel(int x, int y, unsigned char attribute)
{
    int offset = (y * pitch) + (x + 4);
    *((unsigned int*)(frame_buffer + offset)) = vgapal[attribute & 0x0F];
}

/**
 * @brief Functie voor het tekenen van een character
 * @param character 
 * @param x 
 * @param y 
 * @param attribute 
 */
void draw_char(unsigned char character, int x, int y, unsigned char attribute)
{
    int i, j;
    unsigned char *glyph = (unsigned char *)&font + (character < FONT_NUMGLYPHS ? character : 0) * FONT_BPG;

    for (i = 0; i < FONT_HEIGHT; i++) {
        for (j = 0; j < FONT_WIDTH; j++) {
            unsigned char mask = 1 << j;
            unsigned char col = (*glyph & mask) ? attribute & 0x0F : (attribute & 0xF0) >> 4;
        
            draw_pixel(x + j, y + i, col);
        }

        glyph += FONT_BPL;
    }
}

/**
 * @brief Functie voor het tekenen van een hele string naar het scherm
 * @param x 
 * @param y 
 * @param s 
 * @param attribute 
 */
void draw_string(int x, int y, char *str, unsigned char attribute)
{
    while (*str) {
        if (*str == '\r') {
            x = 0;
        } else if (*str == '\n') {
            x = 0;
            y += FONT_HEIGHT;
        } else {
            draw_char(*str, x, y, attribute);
            x += FONT_WIDTH;
        }
        str++;
    } 
}