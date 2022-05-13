#include "io/io.h"
#include "graphics/graphics.h"
#include "io/keyboard.h"
#include "system/interrupts.h"
#include "system/timer.h"


#define RUN 1
#define WIDTH 1920
#define HEIGHT 1080
#define MIN 0
#define MAX 1080
#define STEP_SIZE 20


int length_of_array(const char *);

int m = 0;
int counter = 0;

int step_flag = 0;


struct Henk {
    int x;
    int y;
    int width;
    int height;
};  


struct Henk rectangle;


void verplaats(struct Henk *p, int stepx, int stepy)
{
    moveRect(p->x, p->y, p->width, p->height, STEP_SIZE, 1, 0x0F);

    if (p->x < MIN) {
        step_flag = 0;
    } else if (p->x > MAX) {
        step_flag = 1;
    }

    switch (step_flag)
    {
        case 0: 
            p->x = p->x + stepx;
        break;
        case 1:
            p->x = p->x - stepx;
        break;
    }
    
    p->y = p->y + stepy;
}



/**
 * @brief Hoofdfunctie
 */
void main()
{
    uart_init(1);
    graphics_init();

    timer_load(0);
    // timer_init();

    m = MIN;

    rectangle.x = 400;
    rectangle.y = 100;
    rectangle.width = 100;
    rectangle.height = 40;

    while (RUN) {
        draw_string(m, HEIGHT/2,"Welkom Matej", 0x0f, 7);
        draw_string(WIDTH/5, (HEIGHT/2),"Bij deze een demo met tekst op het scherm!!", 0x0f+counter, 3);

        if (m <= MIN) {
            m += STEP_SIZE;
        } else if (m >= MAX) {
            m += -STEP_SIZE;
        }

        counter++;

        verplaats(&rectangle, STEP_SIZE, 0);

        if (counter >= 20) {
            counter = 0;
        }

        if (get_timer_value() > 5000) {
            draw_string(100, 100, "Timer is nog niet leeg :/", 0x0F+10, 7);
        } else {
            draw_string(100, 500, "Timer is eindelijk leeg :)", 0x0F+10, 7);
        }

        for (int i = 0; i < 400000;i++) {
            asm("nop");
        }

        check_key();
        key_pressed("print");
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