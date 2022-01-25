/*
 * lcd.c
 *
 * Created: 12/2/2021 3:10:13 PM
 *  Author: Admin
 */ 

#ifndef _LCD_C_
#define _LCD_C_


#include "lcd.h"


void lcdCommand( unsigned char cmnd){
	LCD_PRT = (LCD_PRT & 0x0F)|(cmnd & 0xF0);
	LCD_PRT_RS &=~(1<<LCD_RS);   //RS = 0 for command
	//LCD_PRT &=~(1<<LCD_RW);
	LCD_PRT_EN |= (1<<LCD_EN);    // high to low pulse
	_delay_us(1);
	LCD_PRT_EN &=~(1<<LCD_EN);
	_delay_us(200);
	LCD_PRT = (LCD_PRT&0x0F)|(cmnd<<4);
	LCD_PRT_EN |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PRT_EN &= ~(1<<LCD_EN);
	_delay_ms(2);
}

void lcdData (unsigned char data){
	LCD_PRT = (LCD_PRT & 0x0F)|(data & 0xF0);
	LCD_PRT_RS |= (1<<LCD_RS);
	//LCD_PRT &=~(1<<LCD_RW);
	LCD_PRT_EN |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PRT_EN &=~(1<<LCD_EN);
	_delay_us(200);
	LCD_PRT = (LCD_PRT&0x0F)|(data<<4);
	LCD_PRT_EN |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PRT_EN &=~ (1<<LCD_EN);
	_delay_ms(2);
}


void lcd_init(){
	LCD_DDR = 0xFF;
	LCD_DDR_EN |= (1<<LCD_EN);
	LCD_DDR_RS |= (1<<LCD_RS);
	_delay_ms(20);
	LCD_PRT_EN &=~(1<<LCD_EN);   //EN = 0
	//_delay_ms(20);
	lcdCommand(0x33);
	_delay_us(100);
	lcdCommand(0x32);
	_delay_us(100);
	lcdCommand(0x28);
	_delay_us(100);
	lcdCommand(0x0c);
	_delay_us(100);
	lcdCommand(0x01);
	_delay_us(100);
	lcdCommand(0x06);
	_delay_us(100);
	lcdCommand(0x02);		/* send for 4 bit initialization of LCD  */
	_delay_us(100);
	lcdCommand(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	_delay_us(100);
	lcdCommand(0x0c);              /* Display on cursor off*/
	_delay_us(100);
	lcdCommand(0x06);              /* Increment cursor (shift cursor to right)*/
	_delay_us(100);
	lcdCommand(0x01);              /* Clear display screen*/
	_delay_us(100);
	_delay_ms(2);
}


void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char firstCharAdr[]={0x80,0xC0,0x94,0xD4};
	lcdCommand(firstCharAdr[x-1]+y-1);
	_delay_us(100);
}


void lcd_print(char*str)
{
	int i=0;
	for(i=0;str[i]!=0;i++){     ///* Send each char of string till the NULL */
		lcdData(str[i]);
	}
}

void lcd_clear()
{
	lcdCommand(0x01);
	_delay_ms(2);
	lcdCommand(0x80);           //cursor at home position
	_delay_ms(2);
}








#endif /* LCD_C_ */
