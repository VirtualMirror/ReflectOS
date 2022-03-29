#include "io.h"

/**
 * @brief Collection with the important registers of the GPIO pins
 */
enum
{
    GPFSEL0 = PERIPHERAL_BASE + 0x200000,   // GPIO function 0
    GPSET0 = PERIPHERAL_BASE + 0x20001C,    // Verander de output naar 0
    GPCLR0 = PERIPHERAL_BASE + 0x200028,    // Clear de output pin GPIO
    GPPUPPDN0 = PERIPHERAL_BASE + 0x2000E4, // Set pullup or pulldown
};

/**
 * @brief Collection with GPIO specs
 */
enum
{
    GPIO_MAX_PIN = 53, //  Max count GPIO pins
    GPIO_FUNCTION_OUT = 1,
    GPIO_FUNCTION_ALT5 = 2,
    GPIO_FUNCTION_ALT3 = 7, //
};

/**
 * @brief Collection to determine pullup settings
 */
enum
{
    PULL_NONE = 0,
    PULL_DOWN = 1,
    PULL_UP = 2,
};

/**
 * @brief Collection of the AUX register addressess
 */
enum
{
    AUX_BASE = PERIPHERAL_BASE + 0x215000,
    AUX_IRQ = AUX_BASE, // Base address for aux register
    AUX_ENABLES = AUX_BASE + 4,
    AUX_MU_IO_REG = AUX_BASE + 64,
    AUX_MU_IER_REG = AUX_BASE + 68,
    AUX_MU_IIR_REG = AUX_BASE + 72,
    AUX_MU_LCR_REG = AUX_BASE + 76,
    AUX_MU_MCR_REG = AUX_BASE + 80,
    AUX_MU_LSR_REG = AUX_BASE + 84,
    AUX_MU_MSR_REG = AUX_BASE + 88,
    AUX_MU_SCRATCH = AUX_BASE + 92,
    AUX_MU_CNTL_REG = AUX_BASE + 96,
    AUX_MU_STAT_REG = AUX_BASE + 100,
    AUX_MU_BAUD_REG = AUX_BASE + 104,
    AUX_UART_CLOCK = 500000000,
    UART_MAX_QUEUE = 16 * 1024,
};

/**
 * @brief Variabelen
 */
unsigned char uart_output_queue[UART_MAX_QUEUE];
unsigned char uart_output_queue_write = 0;
unsigned char uart_output_queue_read = 0;

/**
 * @brief Function to write to memory
 * @param reg
 * @param value
 */
void mmio_write(long reg, unsigned int value)
{
    *(volatile uint16_t *)reg = value;
}

/**
 * @brief Function to read from memory
 * @param reg
 */
uint16_t mmio_read(long reg)
{
    return *(volatile uint16_t *)reg;
}

/**
 * @brief Function to make an io call
 * @param pin_number
 * @param value
 * @param base
 * @param field_size
 * @param field_max
 * @return unsigned int
 */
uint16_t gpio_call(uint16_t pin_number, uint16_t value, uint16_t base, uint16_t field_size, uint16_t field_max)
{
    uint16_t field_mask = (1 << field_size) - 1;

    if (pin_number > field_mask) {
        return 0;
    }
    if (value > field_mask) {
        return 0;
    }

    uint16_t num_fields = 32 / field_size;
    uint16_t reg = base + ((pin_number / num_fields) * 4);
    uint16_t shift = (pin_number % num_fields) * field_size;

    uint16_t curval = mmio_read(reg);
    curval &= ~(field_mask << shift);
    curval |= value << shift;
    mmio_write(reg, curval);

    return 1;
}

/**
 * @brief Function to enable the GPIO pin
 * @param pin_number
 * @param value
 * @return uint16_t
 */
uint16_t gpio_set(uint16_t pin_number, uint16_t value)
{
    return gpio_call(pin_number, value, GPSET0, 1, GPIO_MAX_PIN);
}

/**
 * @brief Function to clear the GPIO pin
 * @param pin_number
 * @param value
 * @return uint16_t
 */
uint16_t gpio_clear(uint16_t pin_number, uint16_t value)
{
    return gpio_call(pin_number, value, GPCLR0, 1, GPIO_MAX_PIN);
}

/**
 * @brief Function to enable GPIO pullup resistor
 * @param pin_number
 * @param value
 * @return uint16_t
 */
uint16_t gpio_pull(uint16_t pin_number, uint16_t value)
{
    return gpio_call(pin_number, value, GPPUPPDN0, 2, GPIO_MAX_PIN);
}

/**
 * @brief Function to determine the function of the current GPIO pin
 * @param pin_number
 * @param value
 * @return uint16_t
 */
uint16_t gpio_function(uint16_t pin_number, uint16_t value)
{
    return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN);
}

/**
 * @brief Function to set gpio as alternative function 3
 * @param pin_number
 */
void gpio_use_as_alt3(uint16_t pin_number)
{
    gpio_pull(pin_number, PULL_NONE);
    gpio_function(pin_number, GPIO_FUNCTION_ALT3);
}

/**
 * @brief Function to set gpio as alternative function 5
 * @param pin_number
 */
void gpio_use_as_alt5(uint16_t pin_number)
{
    gpio_pull(pin_number, PULL_NONE);
    gpio_function(pin_number, GPIO_FUNCTION_ALT5);
}

/**
 * @brief
 * @param pin_number
 */
void gpio_init_output_pin_with_pull_none(uint16_t pin_number)
{
    gpio_pull(pin_number, PULL_NONE);
    gpio_function(pin_number, GPIO_FUNCTION_OUT);
}

/**
 * @brief
 * @param pin_number 
 * @param on_off 
 */
void gpio_set_pin_output_bool(uint16_t pin_number, uint8_t on_off)
{
    if (on_off)
    {
        gpio_set(pin_number, 1);
    }
    else
    {
        gpio_clear(pin_number, 1);
    }
}

/**
 * @brief Function to setup uart interface
 * @param uart
 */
void uart_init(uint8_t uart)
{
    mmio_write(AUX_ENABLES, uart); // Enables uart
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_CNTL_REG, 0);
    mmio_write(AUX_MU_LCR_REG, 3); // Write 8 bits
    mmio_write(AUX_MU_MCR_REG, 0);
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_IIR_REG, 0xC6); // Disable interupts
    mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(AUX_BAUD_RATE));
    gpio_use_as_alt5(14);
    gpio_use_as_alt5(15);
    mmio_write(AUX_MU_CNTL_REG, 3); // Enable RX/TX
}

/**
 * @brief Functie voor het checken of the output queue leeg is
 * @return uint16_t 
 */
uint16_t uart_is_output_queue_empty()
{
    return uart_output_queue_read == uart_output_queue_write;
}

/**
 * @brief
 * @return uint16_t 
 */
uint16_t uart_is_read_byte_ready()
{
    return mmio_read(AUX_MU_LSR_REG) & 0x01;
}

/**
 * @brief
 * @return uint16_t
 */
uint16_t uart_is_write_byte_ready()
{
    return mmio_read(AUX_MU_LSR_REG) & 0x20;
}

/**
 * @brief Functie voor het lezen van data uit de aux io reg
 * @return unsigned char 
 */
unsigned char uart_read_byte()
{
    while (!uart_is_read_byte_ready());
    return (unsigned char)mmio_read(AUX_MU_IO_REG);
}

/**
 * @brief
 * @param character
 */
void uart_write_byte_blocking_actual(unsigned char character)
{
    while (!uart_is_write_byte_ready());
    mmio_write(AUX_MU_IO_REG, (uint16_t)character);
}

/**
 * @brief
 */
void uart_load_output_fifo()
{
    while (!uart_is_output_queue_empty() && uart_is_write_byte_ready()) {
        uart_write_byte_blocking_actual(uart_output_queue[uart_output_queue_read]);
        uart_output_queue_read = (uart_output_queue_read + 1) & (UART_MAX_QUEUE - 1);
    }
}

/**
 * @brief Functie om data naar de queue te schrijven
 * @param character 
 */
void uart_write_byte_blocking(unsigned char character)
{
    uint16_t next = (uart_output_queue_write + 1) & (UART_MAX_QUEUE - 1);

    while (next == uart_output_queue_read) {
        uart_load_output_fifo();
    }

    uart_output_queue[uart_output_queue_write] = character;
    uart_output_queue_write = next;
}

/**
 * @brief Function to write data to uart
 * @param buffer
 */
void uart_write_text(char *buffer)
{
    while (*buffer)
    {
        if (*buffer == '\n')
        {
            uart_write_byte_blocking_actual('\r');
        }

        uart_write_byte_blocking_actual(*buffer++);
    }
}

/**
 * @brief Functie om de queue te legen
 */
void uart_drain_output_queue()
{
    while (!uart_is_output_queue_empty()) {
        uart_load_output_fifo();
    }
}

/**
 * @brief Functie om de data in de uart registers te updaten
 */
void uart_update()
{
    uart_load_output_fifo();

    if (uart_is_read_byte_ready()) {
        unsigned char character = uart_read_byte();
        if (character == '\r') {
            uart_write_text("\n");
        } else {
            uart_write_byte_blocking(character);
        }
    }
}