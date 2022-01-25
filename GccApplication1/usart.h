/*
 * function.h
 *
 * Created: 12/2/2021 3:07:44 PM
 *  Author: Admin
 */ 


#ifndef _USART_H_
#define _USART_H_


#define F_CPU 16000000// UL // Clock Speed phai define f_cpu truoc khi include delay.h, define cac thu truoc khi add thu vien
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>



void USART_Init(unsigned int );
void USART_Transmit(unsigned char );
void uart_send(char*);
void uart_interrupt_init();






#endif /* USART_H_ */