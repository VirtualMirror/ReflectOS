#include "io.h"
#include "graphics.h"

#define RUN 1
#define WIDTH 1920
#define HEIGHT 1080


int counter = 0;


/**
 * @brief Hoofddunctie
 */
void main()
{
    uart_init(1);
    graphics_init();

    while (RUN) {
        draw_string((WIDTH/2)-40, HEIGHT/2,"Welkom Matej", 0x0f + counter, 3);
        draw_string(WIDTH/5, (HEIGHT/2)+40,"Bij deze een demo met tekst op het scherm!!", 0x0f, 3);

        counter++;

        if (counter == 16) {
            counter = 0;
        }

        for (int i = 0; i < 4000000; i++) {
            asm("nop");
        }
    }
}