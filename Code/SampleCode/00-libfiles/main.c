/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the code to test the ULTRA PIC board.
                Connect the board to system using USB-to-Serial. 
                Reset the board after which the menu will be displayed, select the required option a follow the steps.

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    Copyright (C) 2012  ExploreEmbedded

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/

#include "uart.h"
#include  "rtc.h" 
#include  "i2c.h"
#include  "lcd.h"
#include "delay.h"
#include "keypad.h"
#include "eeprom.h"
#include "gpio.h"
#include "adc.h"

void gpio_test(void);
void LCD_8bit_test(void);
void LCD_4bit_test(void);
void seg_test(void);
void rtc_test(void);
void adc_test(void);
void keypad_test(void);
void eeprom_test(void);


#define LedOn 0xFF
#define LedOff 0x00
#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08




#define SegmentValue PORTC //PORT2.0 is connected to segment 'a'
#define SegmentSlection PORTA //PORT0.0 is selection line 'S1'
#define SegValueDirnReg TRISC
#define SegSelectDirnReg TRISA




char mm_option;

/* start the main program */
void main() 
{
   UART_Init(9600);
   UART_TxString("\n\rTest menu Ultra PIC v2.0\r\n 1:GPIO Blink\r\n 2:LCD 8-bit \n\r 3:LCD 4-bit\n\r 4:7-Segment\n\r 5:RTC\n\r 6:EEPROM\n\r 7:ADC\n\r 8:Keypad \n\r Enter option:");
   UART_TxString("\n\rReset the board after test is done");
   mm_option = UART_RxChar();
   while(1)
    {
 	  	switch(mm_option)
		{
		 case '1': gpio_test(); break;
		 case '2': LCD_8bit_test(); break;
		 case '3': LCD_4bit_test(); break;
		 case '4': seg_test(); break;
		 case '5': rtc_test(); break;
		 case '6': eeprom_test(); break; //eeprom
		 case '7': adc_test(); break;
		 case '8': keypad_test();break;
		 default:break;
		}
	}
}


/******************************************************GPIO TEST*************************************
   Turns ON and OFF all the ports of the 8051 micrcontroller. With the help of this you can  
 *****************************************************GPIO TEST**************************************/

void gpio_test()
{   
   UART_Printf("\n\rConnect any IO Pins to buzzer, relays, leds ");
   UART_Printf("\n\rMake connections and hit 'k' to test ");
   while(UART_RxChar()!='k');
   TRISA = TRISB = TRISC=TRISD = C_PortOutput_U8;
  while(1)
    {
	 /* Turn On all the leds and wait for one second */ 
	   PORTA= PORTB = PORTC =PORTD= 0xff;
	   DELAY_sec(1);
	 /* Turn off all the leds and wait for one second */
	   PORTA= PORTB = PORTC =PORTD= 0x00;
	   DELAY_sec(1);
    }
}

/******************************************************LCD TEST*************************************
					On board LCD TEST in 8 bit mode.
*****************************************************LCD TEST**************************************/

void LCD_8bit_test()
{     
     UART_TxString("\n\r LCD DataBus: PD Control: RS-PB.0 RW-PB.1 EN-PB.2 ");
	  UART_Printf("\n\r Make connections and hit 'k' to test ");
	  while(UART_RxChar()!='k');
	  LCD_Setup(PB_0,PB_1,PB_2,PD_0,PD_1,PD_2,PD_3,PD_4,PD_5,PD_6,PD_7);
	  LCD_Init(2,16);
	  DELAY_ms(100);
	  LCD_DisplayString("Explore Embedded");
	  LCD_DisplayString("Lcd 8-bit Mode");
	  while(1);
}



void LCD_4bit_test()
{
     UART_TxString("\n\r LCD DataBus: PC Msb bits(PC4-PC7) Control: RS-PA.0 RW-PA.1 EN-PA.2 ");
      UART_Printf("\n\r Make connections and hit 'k' to test ");
      while(UART_RxChar()!='k');
      LCD_Setup(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PD_4,PD_5,PD_6,PD_7);
      LCD_Init(2,16);
      DELAY_ms(100);
      LCD_DisplayString("Explore Embedded");
      LCD_DisplayString("Lcd 4-bit Mode");
      while(1);
}


/*************************************************SEVEN SEGMENT*************************************
 				Displays numbers 1 2 3 4 on the on-board segments 
*********************************************************TEST**************************************/

void seg_test()
{  
 unsigned char seg_code[]={0xC0,0xF9,0xA4,0xB0}; 
 UART_TxString("\n\r Segment DataBus: P2 Seg select: S1->P0.0 S2->P0.1 S3->P0.2 S4->P0.4  ");
 UART_Printf("\n\rMake connections and hit 'k' to test! ");
 while(UART_RxChar()!='k');
 SegValueDirnReg = C_PortOutput_U8;
 SegSelectDirnReg = C_PortOutput_U8;

	while(1)
	{  
	   SegmentSlection=SegOne;
	   SegmentValue = seg_code[0];
	   DELAY_us(10); 
	   SegmentSlection=SegTwo;
	   SegmentValue = seg_code[1];
	   DELAY_us(10);
	   SegmentSlection=SegThree;
	   SegmentValue = seg_code[2];
	   DELAY_us(10);	
	   SegmentSlection=SegFour;  
	   SegmentValue = seg_code[3];
	   DELAY_us(10);
	 }  
}

/***************************************************RTC DS1307*************************************
 				Displays time on UART, reading from the RTC
*********************************************************TEST**************************************/

void rtc_test()
{
    unsigned char sec,min,hour,day,month,year;
    UART_Printf("\n\rConnections SCL->P0.6 SDA->P0.7");
	UART_Printf("\n\r Make connections and hit 'k' to test! ");
    while(UART_RxChar()!='k');   

	RTC_Init();

	
 /*##### Set the time and Date only once. Once the Time and Date is set, comment these lines
         and reflash the code. Else the time will be set every time the controller is reset*/
    RTC_SetTime(0x10,0x40,0x00);  //  10:40:20 am
    RTC_SetDate(0x01,0x01,0x15);  //  1st Jan 2015

   /* Display the Time and Date continuously */ 
   while(1)
    {
        RTC_GetTime(&hour,&min,&sec);      
        RTC_GetDate(&day,&month,&year);        
        UART_Printf("\n\rtime:%2x:%2x:%2x  \nDate:%2x/%2x/%2x",(uint16_t)hour,(uint16_t)min,(uint16_t)sec,(uint16_t)day,(uint16_t)month,(uint16_t)year);
     }
    
   
}

/***************************************************EEPROM*****************************************
 				Writes and Reads a character to and from EEPROM
*****************************************************TEST*****************************************/
void eeprom_test()
{
	 unsigned char eeprom_aTRISess=0x00, write_char = 'X', read_char;
	 
	UART_Printf("Connections SCL->P0.6 SDA->P0.7");
	UART_Printf("Make connections and hit 'k' to test! ");
        while(UART_RxChar()!='k');
	 UART_TxString("\n\rEeprom Write: ");      //Print the message on UART
	 UART_TxChar(write_char);			         //Print the char to be written 
	 EEPROM_WriteByte(eeprom_aTRISess,write_char);	// Write the data at memoryLocation	0x00

	 UART_TxString("  Eeprom Read: ");            //Print the message on UART
	 read_char = EEPROM_ReadByte(eeprom_aTRISess);	// Read the data from memoryLocation 0x00
	 UART_TxChar(read_char);	
}

/***************************************************ADC *****************************************
 				Reads and displays ADC data from on board sensors.
*****************************************************TEST*****************************************/
void adc_test()
{ 
 uint16_t temp,light,pot;
 UART_Printf("\n\rConnections: DataBus P1 Control: adc_A->P0.0 adc_B->P0.1 adc_C->P0.2 adc_ALE->P.3 adc_Start->P.4 adc_EOC->P1.5 adc_OE->P1.6");
 UART_Printf("\n\rMake connections and hit 'k' to test!");
 while(UART_RxChar()!='k');
 ADC_Init();

 while(1)
 {
   temp = ADC_GetAdcValue(0);
   pot = ADC_GetAdcValue(1);
   light = ADC_GetAdcValue(2);
   UART_Printf("\n\rtemp:%3d pot:%3d light:%3d", temp,pot,light);

 }
}


/***************************************************KEYPAD *****************************************
 				Displays keys pressed on 4x4 keypad on the uart
*****************************************************TEST*******************************************/
void keypad_test()
{
uint8_t key;
UART_Printf("\n\rConnections: Port 2");
UART_Printf("\n\rMake connections and hit 'k' to test!");
while(UART_RxChar()!='k');
KEYPAD_Init();
while(1)
{
  key = KEYPAD_GetKey();
  UART_Printf("\n\r Key:%c", key);
}
}













