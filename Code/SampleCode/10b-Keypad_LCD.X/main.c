/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   keypad.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This files contains the program to read the key pressed on 4x4 hex keypad and display it on LCD.

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

#include "keypad.h"
#include "lcd.h"


int main() 
{
    uint8_t key;

    /*Connect RS->PB0, RW->PB1, EN->PB2 and data bus PORTB.4 to PORTB.7*/
    LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PB_4,PB_5,PB_6,PB_7);
    LCD_Init(2,16);
    
    KEYPAD_Init(PD_0,PD_1,PD_2,PD_3,PD_4,PD_5,PD_6,PD_7);
    
    LCD_Printf("Key Pressed:");
    while (1) 
    {
        key = KEYPAD_GetKey();
        LCD_GoToLine(1);
        LCD_DisplayChar(key);
        
    }

    return (0);
}

