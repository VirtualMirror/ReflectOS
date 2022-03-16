#include "io.h"

/**
 * @brief Collection with Settings voor GPIO
 * 
 */
enum {
    PERIPHERAL_BASE = 0xFE000000,                       // Basis adres voor GPIO
    GPFSEL0         = PERIPHERAL_BASE + 0x200000,       // GPIO function 0
    GPSET0          = PERIPHERAL_BASE + 0x20001C,       // Verander de output naar 0
    GPCLR0          = PERIPHERAL_BASE + 0x200028,       // Clear de output pin GPIO
    GPPUPPDN0       = PERIPHERAL_BASE + 0x2000E4,       // ?
};


/**
 * @brief Collection with GPIO specs
 * 
 */
enum {
    GPIO_MAX_PIN        = 53,                           //  
    GPIO_FUNCTION_ALT5  = 2,                            //
};


/**
 * @brief Random collection
 * 
 */
enum {
    PULL_NONE = 0,
};  


/**
 * @brief 
 * 
 * @param reg
 * @param value 
 */
void mmio_write(long reg, unsigned int value)
{
    *(volatile unsigned int *)reg = value;
}


/**
 * @brief 
 * 
 * @param reg
 */
unsigned int mmio_read(long reg)
{
    
}