#include "io/io.h"
#include "graphics/graphics.h"
#include "io/keyboard.h"
#include "system/interrupts.h"
#include "system/timer.h"
#include "views/home_view.h"
#include "system/scheduler.h"


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


/**
 * @brief Hoofdfunctie
 */
void main()
{
    uart_init(1);
    init_memory();
    graphics_init();
    init_scheduler();
    init_screen();

    add_task_to_scheduler("Custom task", "test1", 0);

    // draw_string(400, 800, "Nog een test", 0x0f, 9);

    // timer_load(0);
    // timer_init();

    home_screen_init();

    while (RUN) {
        if (check_for_empty_scheduler() != 0) {
            reshift_scheduler();
        } else {
            draw_string(400, 600, "Scheduler is leeg", 0x0f, 8);
        }

        home_screen_draw(); 

        clear_screen(0x0f+40);       

        if (counter >= 100) {
            counter = 0;
        }

        counter = counter + STEP_SIZE;
    }
}