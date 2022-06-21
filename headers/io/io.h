#pragma once


#ifndef __IO__
#define __IO__

#define AUX_MU_BAUD(baud) ((500000000/(baud*8))-1)
#define AUX_BAUD_RATE 115200
#define PERIPHERAL_BASE 0xFE000000


void gpio_use_as_alt3(unsigned int);
void gpio_use_as_alt5(unsigned int);

void uart_init(unsigned short);
void uart_write_text(char *);
void uart_load_output_fifo();
unsigned char uart_read_byte();
unsigned int uart_is_read_byte_ready();
void uart_write_byte_blocking(unsigned char);
void uart_update();
void mmio_write(long, unsigned int);
unsigned int mmio_read(long);
void uart_hex(unsigned int);
void uart_byte(unsigned char);


#endif