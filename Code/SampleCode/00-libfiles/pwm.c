
/***************************************************************************************************
                                   ExploreEmbedded    
 ****************************************************************************************************
 * File:   pwm.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for PWM generation for Pic16f877a controllers

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
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
#include "pwm.h"
#include "stdutils.h"

#pragma warning push
#pragma warning disable 752 // Suppress warnings related to size of variables(conversion to shorter data type).


/***************************************************************************************************
                        void PWM_Init(void)
 ****************************************************************************************************
 * I/P Arguments   : none
 * Return value    : none

 * description :This function initializes the Timer2 module for generating the PWM using timers.
 ***************************************************************************************************/
void PWM_Init(uint8_t channel)
{
    switch (channel)
    {
    case 0 :
        CCP1CON = 0x0F; // Select the PWM mode.
        PR2 = 100;      // Set the Cycle time to 100 for varying the duty cycle from 0-100
        CCPR1L = 50;    // By default set the dutycycle to 50
        util_BitClear(TRISC,2); // Make the PWM pin(PC.2) Output
        break;

    case 1 :
        CCP2CON = 0x0F; // Select the PWM mode.
        PR2 = 100;      // Set the Cycle time to 100 for varying the duty cycle from 0-100
        CCPR2L = 50;    // By default set the dutycycle to 50
        util_BitClear(TRISC,1); // Make the PWM pin(PC.1) Output
        break;
    }
}







/***************************************************************************************************
                         void PWM_SetDutyCycle( uint8_t channel, uint8_t dutyCycle )
 ****************************************************************************************************
 * I/P Arguments: uint8_t: channel number at which PWM needs to be generated.(0/1).
                  uint8_t : required dutyCycle at the pwm pin(0-100).
 * Return value    : none

 * description :This function is used the set the duty cycle for the required channel.
                Ensure the PWM_Init() function is called before calling this function.
                This function only sets the duty cycle, the actual PWM generation satarts after calling PWM_Start().

Note: By default the dutycyle is set to 50%.
 ***************************************************************************************************/
void PWM_SetDutyCycle(uint8_t channel,uint8_t dutyCycle)
{
    if(dutyCycle>100)
        dutyCycle = 100;

    switch (channel)
    {
    case 0 :
        CCPR1L = dutyCycle;
        break;

    case 1 :
        CCPR2L = dutyCycle;
        break;
    }
}






/***************************************************************************************************
                         void PWM_Start(uint8_t channel)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to start the pwm generation for the required channel.
 ***************************************************************************************************/
void PWM_Start(uint8_t channel)
{
    TMR2ON = 1; //Start the Timer for PWM generation
}




/***************************************************************************************************
                         void PWM_Start(uint8_t channel)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to stop the pwm generation for the required channel.
 ***************************************************************************************************/
void PWM_Stop(uint8_t channel)
{
    switch (channel)
    {
    case 0 :
        CCP1CON = 0x00;  //Disable the CCP Module from generating PWM
        break;

    case 1 :
        CCP2CON = 0x00;  //Disable the CCP Module from generating PWM
        break;
    }
}

#pragma warning pop