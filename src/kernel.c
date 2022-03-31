#include "io.h"
#include "graphics.h"


#define RUN 1
#define WIDTH 1280
#define HEIGHT 720


/**
 * @brief Hoofddunctie
 * 
 */
void main()
{
    uart_init(1);
    graphics_init();

    draw_string(100, 100,"Als het nou niet boot is het een pussy",0x0f);

    while (RUN);
}