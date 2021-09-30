#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	while(get32(UART_FR) & (1 << 5)) 
		;
	put32(UART_DR,c);
}

char uart_recv ( void )
{
	while(get32(UART_FR) & (1<<4))
		;
	return(get32(UART_DR)&0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
	unsigned int selector;
	
	put32(UART_CR, 0);
	put32(UART_IMSC, 0);

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt0 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt0 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);


	put32(UART_IBRD, 26);
	put32(UART_FBRD, 3);
	put32(UART_LCRH, (3 << 5) | (1 << 4));
	put32(UART_CR, (1 << 9) | (1 << 8) | (1 << 0));
}
