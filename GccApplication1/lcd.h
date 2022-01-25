/*
 * lcd.h
 *
 * Created: 12/2/2021 3:10:03 PM
 *  Author: Admin
 */ 


#ifndef _LCD_H_
#define _LCD_H_

#define F_CPU 16000000// UL // Clock Speed phai define f_cpu truoc khi include delay.h, define cac thu truoc khi add thu vien


#define  LCD_PRT PORTD
#define LCD_DDR DDRD
#define LCD_PRT_RS PORTB
#define LCD_PRT_EN PORTB
#define LCD_DDR_RS DDRB
#define LCD_DDR_EN DDRB
#define  LCD_RS 1
//#define  LCD_RW
#define  LCD_EN 0



#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>





void lcdCommand( unsigned char );
void lcdData (unsigned char data);
void lcd_init();
void lcd_gotoxy(unsigned char , unsigned char );
void lcd_print(char*);
void lcd_clear();






#endif /* LCD_H_ */