#include "io.h"
#include "graphics.h"

#define RUN 1

/**
 * @brief Hoofddunctie
 */
int main()
{
    uart_init(1);
    init_graphics();

    draw_pixel(250,250,0x0e);

    draw_character('O',500,500,0x05);
    draw_string(100,100,"Hello world!",0x0f);

    while (1);
}