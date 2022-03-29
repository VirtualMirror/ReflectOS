#include "io.h"
#include "graphics.h"


#define RUN 1


/**
 * @brief Hoofddunctie
 * 
 */
int main()
{
    uart_init(1);
    init_graphics();

    drawPixel(250,250,0x0e);

    drawChar('O',500,500,0x05);
    drawString(100,100,"Hello world!",0x0f);

    while (1);
}