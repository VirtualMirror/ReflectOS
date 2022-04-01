#include "io/io.h"
#include "system/timer.h"


/**
 * @brief Collectie met de timer registers
 * 
 */
enum
{
    BASE            = 0x7e00b000,
    TIMER_LOAD      = BASE + 0x400,
    TIMER_VALUE     = BASE + 0x404,
    TIMER_CONTROL   = BASE + 0x408,
    TIMER_IRQ_CNTL  = BASE + 0x40c,
    TIMER_RAW_IRQ   = BASE + 0x410,
    TIMER_MSK_IRQ   = BASE + 0x414,
    TIMER_RELOAD    = BASE + 0x418,
    TIMER_PRE_DIV   = BASE + 0x41c,
    TIMER_FREE_CNT  = BASE + 0x420,
};


/**
 * @brief Collectie met waardes voor de TIMER CONTROL Register
 * 
 */
enum
{
    FREE_DIV        = 18, // in 804 timer, Deze bits bestaan niet
    ENA_FREE        = 9,
    DBG_HALT        = 8,
    ENABLE          = 7,
    IRQ_EN          = 5,
    DIV1            = 3,
    DIV2            = 2,
    BIT32           = 1,
};


/**
 * @brief Functie voor het opzetten van de timer
 * 
 */
void timer_init()
{
    mmio_write(TIMER_CONTROL, (1<<ENABLE) | (1<<IRQ_EN) | (1<<BIT32));
}


/**
 * @brief Functie voor het laden van de timer met een specifieke waarde
 * 
 * @param value 
 */
void timer_load(long value)
{
    mmio_write(TIMER_LOAD, value);
}


/**
 * @brief Functie voor het resetten van de timer
 * 
 */
void timer_IRQ_clear()
{
    mmio_write(TIMER_IRQ_CNTL, 1);
}


/**
 * @brief Get the timer value object
 * 
 * @return unsigned long 
 */
unsigned long get_timer_value()
{
    return mmio_read(TIMER_VALUE);
}