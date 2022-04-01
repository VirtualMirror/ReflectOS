#include "io.h"
#include "graphics.h"
#include "keyboard.h"
#include "interrupts.h"
#include "timer.h"

#define RUN 1
#define WIDTH 1920
#define HEIGHT 1080


int length_of_array(const char *);


int counter = 0;


/**
 * @brief Hoofdfunctie
 */
void main()
{
    uart_init(1);
    graphics_init();

    while (RUN) {
        draw_string((WIDTH/2)-((length_of_array("Welkom Matej")*7)/2), HEIGHT/2,"Welkom Matej", 0x0f + counter, 7);
        draw_string(WIDTH/5, (HEIGHT/2)+140,"Bij deze een demo met tekst op het scherm!!", 0x0f, 3);

        counter++;

        if (counter == 16) {
            counter = 0;
        }

        for (int i = 0; i < 4000000; i++) {
            asm("nop");
        }

        key_pressed();
    }
}


/**
 * @brief Functie om de grootte van een string te krijgen
 * @param string 
 * @return int 
 */
int length_of_array(const char *string)
{
    int size;

    while (*string) {
        size++;
        string++;
    }

    return size;
}