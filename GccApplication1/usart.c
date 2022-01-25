/*
 * function.c
 *
 * Created: 12/2/2021 3:07:33 PM
 *  Author: Admin
 */ 
#ifndef _USART_C_
#define _USART_C_

#include "usart.h"


void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)))
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


/*void uart_send(unsigned char ch){
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=ch;
}*/

void uart_send(char*str)
{
	int i=0;
	for(i=0;str[i]!=0;i++){     ///* Send each char of string till the NULL */
		USART_Transmit(str[i]);
	}
}

void uart_interrupt_init()
{
	UCSR0B|=(1<<RXCIE0);
}








#endif /* USART_C_ */
