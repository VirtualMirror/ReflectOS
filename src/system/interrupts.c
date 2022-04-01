#include "io/io.h"
#include "system/interrupts.h"
#include "system/timer.h"


#define INTERRUPT_NAME_LENGTH 30
#define TABLE_WIDTH 6
#define TABLE_HEIGHT 8



/**
 * @brief Collectie met de type interrupts die voorkomen
 * 
 */
enum {
    TIMER,
    SOFTWARE,
    DOORBELL,
    UART,
    MAILBOX,
};


/**
 * @brief Collectie met de verschillende interrupts addressen
 * 
 */
enum 
{
    BASE                = 0x4c0000000, // Als low peripheral mode aanstaat is het 0xff800000.
    ARM_CONTROLL        = BASE,             
    CORE_IRQ_CONTROL    = BASE + 0x0C,
    PMU_CONTROL_SET     = BASE + 0x10,
    PMU_CONTROL_CLR     = BASE + 0x14,
    PERI_IRQ_ROUTE0     = BASE + 0x24,
    AXI_QUIET_TIME      = BASE + 0x30,
    LOCAL_TIMER_CONTROL = BASE + 0x34,
    LOCAL_TIMER_IRQ     = BASE + 0x38,
    TIMER_CTRL_0        = BASE + 0x40,
    MAILBOX_CTRL_0      = BASE + 0x50,
    IRQ_SOURCE_0        = BASE + 0x60,
    FIQ_SOURCE_0        = BASE + 0x70,
};


/**
 * @brief Collectie met de waardes van de ARM CONTROL Register
 * 
 */
enum 
{
    TIMER_INCREMENT     = 8,
    PROC_CLK_TIMER      = 7,
    AXIERRIRQ_EN        = 6,
};


/**
 * @brief Collectie met waardes voor de LOCAL TIME Controller
 * 
 */
enum 
{
    TIMER_IRQ_FLAG      = 31,
    TIMER_IRQ_EN        = 29,
    TIMER_EN            = 28,
};


/**
 * @brief Collectie met de waardes voor de LOCAL TIMER Register
 * 
 */
enum
{
    IRQ_CLEAR       = 31,
    RELOAD          = 30,
};


/**
 * @brief Structure die de data vast houd voor een interrupt
 * 
 */
typedef struct {
    char title[INTERRUPT_NAME_LENGTH];
    unsigned int type;
} interrupt;


interrupt interrupt_vector_table[TABLE_WIDTH][TABLE_HEIGHT];


unsigned int counterX = 0;
unsigned int counterY = 0;


/**
 * @brief Functie om alle interrupt waardes op te zetten
 * 
 */
void interrupts_init()
{
    timer_init();

    mmio_write(ARM_CONTROLL, 0);
}


/**
 * @brief Functie voor het toevoegen van een interrupt aan de interrupt table
 * 
 * @param inter 
 */
void add_interrupt(interrupt inter)
{   
    interrupt_vector_table[counterX][counterY] = inter;
    counterY++;

    if (counterY >= TABLE_HEIGHT) {
        counterX++;
        counterY = 0;
    }
}


/**
 * @brief Functie voor het uitvoeren van een interrupt
 * 
 */
void execute_interrupt()
{
    interrupt_vector_table[counterX][counterY].title;
}


/**
 * @brief 
 * 
 */
void enable_timer_interrupt()
{
    mmio_write(LOCAL_TIMER_CONTROL, (1<<TIMER_IRQ_EN) | (1<<TIMER_EN));
    mmio_write(LOCAL_TIMER_IRQ, 0);

    timer_load(8000000);
}