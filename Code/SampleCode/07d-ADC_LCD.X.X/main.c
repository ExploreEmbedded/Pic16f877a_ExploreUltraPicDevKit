/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to read 10bit ADC value from channel 0 and display the Raw and Equivalent volt on LCD.

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
    float volt;
    
    ADC_Init();       /* Initialize the ADC module */
    
    /*Connect RS->PB0, RW->PB1, EN->PB2 and data bus PORTB.4 to PORTB.7*/
    LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PB_4,PB_5,PB_6,PB_7);
    LCD_Init(2,16);
    
    while(1)
    {
        adcValue = ADC_GetAdcValue(0); // Read the ADC value of channel zero
        volt = (adcValue*5.00)/1023;
        LCD_GoToLine(0);
        LCD_Printf("ADC0 Value:%4d\nVolt:%f",adcValue,volt);     // Display Raw adc value and Equivalent temp on LCD
    }
    
    return (0);
}


