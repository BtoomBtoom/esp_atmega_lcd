

#define F_CPU 16000000// UL // Clock Speed phai define f_cpu truoc khi include delay.h, define cac thu truoc khi add thu vien
#define FOSC 16000000 // try replacing FOSC with F_CPU see what happend?  FOSC is just out own created parameter
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

//#define  LCD_PRT PORTD
//#define LCD_DDR DDRD
//#define  LCD_RS 3
////#define  LCD_RW
//#define  LCD_EN 2

#include "usart.h"
#include "lcd.h"






volatile int luu_tru_ready = 0;
char luu_tru[100]={0};
volatile int bien_dem_luu_tru = 0; 




int main(){
	char data_temp_1[3],data_hum_1[3];
	char ID_1[] = "4C:75:25:06:A1:E7"; //ID hien dang co


	char data_temp_2[3],data_hum_2[3];
	char ID_2[] = "AC:0B:FB:CE:AD:1F";   // ID hien dang co;
	
	char data_temp_3[3],data_hum_3[3];
	char ID_3[] = "EC:FA:BC:5F:84:A9"; //ID hien dang co

	char *real_time_data_temp,*real_time_data_hum,*real_time_ID;


	char luu_tru_ID[18];   // dung ham for lay tung chu cai id ra luu vao day
	// neu luu tung ki tu thi them ky tu null vao cuoi cung de thanh string

	int du_lieu_temp_1[50]={0};
	int du_lieu_hum_1[50]={0};


	int du_lieu_temp_2[50]={0};
	int du_lieu_hum_2[50]={0};
		
	int du_lieu_temp_3[50]={0};
	int du_lieu_hum_3[50]={0};

	int bien_dem_1=0,temp_1=0,hum_1=0,temp_tb_1=0,hum_tb_1=0;

	int bien_dem_2=0,temp_2=0,hum_2=0,temp_tb_2=0,hum_tb_2=0;
	
	int bien_dem_3=0,temp_3=0,hum_3=0,temp_tb_3=0,hum_tb_3=0;

	char a1[50],a2[50]; // de luu cac string "re" va "ty"
	lcd_init();
	USART_Init(MYUBRR);  
	sei();
	uart_interrupt_init();  // init pin change interrupt 7 and 8, RX complete interrupt
	
	DDRC =0;    //PC1 and PC2 are input
	PORTC |=(1<<PINC1)|(1<<PINC2)|(1<<PINC3);			//PINC1 and PINC2 and PINC3 internal pull-resister enable
	
	
	
	
	
	
	
	
	
	
	//new code
	int button_1_before = 1;
	int button_1;
	int button_2_before = 1;
	int button_2;
	 
	
	char* data_temp[] = {data_temp_1, data_temp_2, data_temp_3};
	char* data_hum[] = {data_hum_1, data_hum_2, data_hum_3};
	char* ID[] = {ID_1, ID_2, ID_3}; 
	int index = 0;
	real_time_data_temp = data_temp[index];
	real_time_data_hum = data_hum[index];
	real_time_ID = ID[index];
	//end
	
	
	while(1)
	{
		
		if(luu_tru_ready == 1 )
		{
				int i=0;
				for(i=7;i<=23;i++)
				{
					luu_tru_ID[i-7]=luu_tru[i];
				}
				luu_tru_ID[17] = '\0';   // luu ID gui den vao luu_tru_ID

		
		
				if(strcmp(luu_tru_ID,ID_1) == 0)// truong hop neu la ID_1
					{
					   int k=0;
					   int j=0;
					 
					   strcpy(a1,strstr(luu_tru,"re"));
					   strcpy(a2,strstr(luu_tru,"ty"));
					   temp_1=(a1[4]-'0')*10+(a1[5]-'0');
					   hum_1=(a2[4]-'0')*10+(a2[5]-'0');
					   du_lieu_temp_1[bien_dem_1]=temp_1;
					   du_lieu_hum_1[bien_dem_1]=hum_1;
			   

					   do
					   {
						   temp_tb_1+=du_lieu_temp_1[j];
						   j++;
						   if(j==50)break;
					   }while(du_lieu_temp_1[j]!='\0');
					   temp_tb_1/=j;
					   itoa(temp_tb_1,data_temp_1,10);//kiem tra lai xem ky tu cuoi cua data_temp_1 co phai la null chua thi moi la string dc
			
					   do
					   {
						   hum_tb_1+=du_lieu_hum_1[k];

						   k++;
						   if(k==50)break;
					   }while(du_lieu_hum_1[k]!='\0');
					   hum_tb_1/=k;
					   itoa(hum_tb_1,data_hum_1,10);
			   
					   temp_tb_1=0; //reset lai bien tem_tb
					   hum_tb_1=0;   // reset lai hum_tb
					   bien_dem_1++;
					   if(bien_dem_1==50){bien_dem_1=0;}
					}   
			
			
				if(strcmp(luu_tru_ID,ID_2) == 0) // neu la ID_2
				{
					   int k=0;
					   int j=0;
					   strcpy(a1,strstr(luu_tru,"re"));
					   strcpy(a2,strstr(luu_tru,"ty"));
					   temp_2=(a1[4]-'0')*10+(a1[5]-'0');
					   hum_2=(a2[4]-'0')*10+(a2[5]-'0');
					   du_lieu_temp_2[bien_dem_2]=temp_2;du_lieu_hum_2[bien_dem_2]=hum_2;
			   
			   
			   
					   do
					   {
						   temp_tb_2+=du_lieu_temp_2[j];
						   j++;
						   if(j==50)break;
					   }while(du_lieu_temp_2[j]!='\0');
					   temp_tb_2/=j;
					   itoa(temp_tb_2,data_temp_2,10);
					   do
					   {
						   hum_tb_2+=du_lieu_hum_2[k];

						   k++;
						   if(k==50)break;
					   }while(du_lieu_hum_2[k]!='\0');
					   hum_tb_2/=k;
					   itoa(hum_tb_2,data_hum_2,10);
			   
					   temp_tb_2=0; //reset lai bien tem_tb
					   hum_tb_2=0;   // reset lai hum_tb
					   bien_dem_2++;
					   if(bien_dem_2==50){bien_dem_2=0;}
				}
				
				if(strcmp(luu_tru_ID,ID_3) == 0)// truong hop neu la ID_3
					{
					   int k=0;
					   int j=0;
					   strcpy(a1,strstr(luu_tru,"re"));
					   strcpy(a2,strstr(luu_tru,"ty"));
					   temp_3=(a1[4]-'0')*10+(a1[5]-'0');
					   hum_3=(a2[4]-'0')*10+(a2[5]-'0');
					   du_lieu_temp_3[bien_dem_3]=temp_3;
					   du_lieu_hum_3[bien_dem_3]=hum_3;
			   
			   
					   do
					   {
						   temp_tb_3+=du_lieu_temp_3[j];
						   j++;
						   if(j==50)break;
					   }while(du_lieu_temp_3[j]!='\0');
					   temp_tb_3/=j;
					   itoa(temp_tb_3,data_temp_3,10);//kiem tra lai xem ky tu cuoi cua data_temp_1 co phai la null chua thi moi la string dc
			
					   do
					   {
						   hum_tb_3+=du_lieu_hum_3[k];

						   k++;
						   if(k==50)break;
					   }while(du_lieu_hum_3[k]!='\0');
					   hum_tb_3/=k;
					   itoa(hum_tb_3,data_hum_3,10);
			   
					   temp_tb_3=0; //reset lai bien tem_tb
					   hum_tb_3=0;   // reset lai hum_tb
					   bien_dem_3++;
					   if(bien_dem_3==50){bien_dem_3=0;}
					} 
				
				
				
				
		
		
				bien_dem_luu_tru = 0;
				luu_tru_ready = 0;
				for(int a=0;a<50;a++){
					luu_tru[a]=0;
				}		
		}
		
		
		button_1 = PINC&(1<<PINC1);
		button_2 = PINC&(1<<PINC2);
		
		if(button_1!=button_1_before)
		{
			if(button_1==0)
			{
				index++;
				if(index==3)
				{
					index=0;
				}
				real_time_data_temp = data_temp[index];
				real_time_data_hum = data_hum[index];
				real_time_ID = ID[index];
			}
			button_1_before = button_1;
		}
		
		if(button_2!=button_2_before)
		{
			if(button_2==0)
			{
				index--;
				if(index==-1)
				{
					index=2;
				}
				real_time_data_temp = data_temp[index];
				real_time_data_hum = data_hum[index];
				real_time_ID = ID[index];
			}
			button_2_before = button_2;
		}
		
		
		
		lcd_clear();
	    lcd_print(real_time_ID);
		lcd_gotoxy(2,1);
		lcd_print("tem:");lcd_print(real_time_data_temp);lcdData(0xDF);lcd_print("C ");
		lcd_print("hum:");lcd_print(real_time_data_hum);lcd_print("%");
		_delay_ms(100);
		
			
		
	}
}

ISR(USART_RX_vect)
{
	char c;
	c=UDR0;
	
	if(c=='}')
	{
		bien_dem_luu_tru = 0;
		luu_tru_ready = 1;
	}
	else if(c!='}')
	{
		luu_tru[bien_dem_luu_tru] = c;
		bien_dem_luu_tru++;
	}
}


