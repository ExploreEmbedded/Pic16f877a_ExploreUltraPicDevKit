/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to read the temperature(LM35) from ADC channel 0 and display it on LCD.

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/
#include "adc.h"
#include "lcd.h"



int main() 
{
    int adcValue;
    float temp;
    
    ADC_Init();       /* Initialize the ADC module */
    
    /*Connect RS->PB0, RW->PB1, EN->PB2 and data bus PORTB.4 to PORTB.7*/
    LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PB_4,PB_5,PB_6,PB_7);
    LCD_Init(2,16);
    
    while(1)
    {
        adcValue = ADC_GetAdcValue(0); // Read the ADC value of channel zero where the temperature sensor(LM35) is connected
        
        /* Convert the raw ADC value to equivalent temperature with 5v as ADC reference
		 Step size of AdC= (5v/1023)=4.887mv = 5mv.
		 for every degree celcius the Lm35 provides 10mv voltage change.
	     1 step of ADC=5mv=0.5'c, hence the Raw ADC value can be divided by 2 to get equivalent temp*/
        
        temp = adcValue/2.0; // Divide by 2 to get the temp value.
        LCD_GoToLine(0);
        LCD_Printf("ADC0 Value:%4d \nTemp:%f\n\r",adcValue,temp);     // Display adc value and temp LCD
    }
    
    return (0);
}


