#ifndef __IO__
#define __IO__


#define AUX_MU_BAUD(baud) ((500000000/(baud*8))-1)
#define AUX_BAUD_RATE 115200
#define PERIPHERAL_BASE 0xFE000000


typedef unsigned short uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;


void uart_init(uint8_t uart);
void uart_write_text(char *);
void uart_load_output_fifo();
unsigned char uart_read_byte();
uint16_t uart_is_read_byte_ready();
void uart_write_byte_blocking(unsigned char);
void uart_update();


#endif