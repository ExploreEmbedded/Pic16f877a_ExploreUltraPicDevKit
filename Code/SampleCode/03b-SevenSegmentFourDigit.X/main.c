/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate a four digit decimal up counter. 

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
#include <pic16f877a.h>

#define SegOne   0xfe
#define SegTwo   0xfd
#define SegThree 0xfb
#define SegFour  0xf7	

void DELAY_ms(unsigned int ms_Count) 
{
    unsigned int i, j;
    for (i = 0; i < ms_Count; i++) 
    {
        for (j = 0; j < 100; j++);
    }
}

int main() {
    char seg_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
    int cnt, num, temp,i;

    /* Configure the ports as output */
    TRISB = 0x00;
    TRISD = 0x00;

    while (1) 
    {
        for (cnt = 0x00; cnt <= 9999; cnt++) // loop to display 0-F
        {
            for (i = 0; i < 100; i++)
            {
                num = cnt;
                temp = num / 1000;
                num = num % 1000;
                PORTD = SegOne; 
                PORTB = seg_code[temp];               
                DELAY_ms(1);

                temp = num / 100;
                num = num % 100;
                PORTD = SegTwo; 
                PORTB = seg_code[temp];
                DELAY_ms(1);

                temp = num / 10;
                PORTD = SegThree;
                PORTB = seg_code[temp];
                DELAY_ms(1);

                temp = num % 10;
                PORTD = SegFour;
                PORTB = seg_code[temp];
                DELAY_ms(1);                              
            }
        }
    }
}
