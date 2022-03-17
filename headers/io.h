#ifndef __IO__
#define __IO__


#define AUX_MU_BAUD(baud) ((500000000/(baud*8))-1)
#define AUX_BAUD_RATE 115200


typedef unsigned short uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;


void uart_init(uint8_t uart);
void uart_write(char *);

#endif