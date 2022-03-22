#include "io.h"


#define RUN 1


/**
 * @brief Hoofddunctie
 * 
 */
int main()
{
    uart_init(1);
    uart_write_text("Hellow World!\n");

    while (RUN) {
        uart_update();
    }

    return 0;
}