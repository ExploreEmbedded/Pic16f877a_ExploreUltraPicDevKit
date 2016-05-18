#include<pic16f877a.h>

#define SBIT_ADON     0
#define SBIT_CHS0     3
#define SBIT_ADFM     7

void delay(int cnt)
{
    while(cnt--);
}

void ADC_Init()
 {
   ADCON0=0x00;  // sampling freq=osc_freq/2,ADC off initially
   ADCON1=(1<<SBIT_ADFM);  // All pins are configured as Analog pins and ADC result is right justified  
}


int ADC_Read(int adcChannel)
 {  
    ADCON0 = (1<<SBIT_ADON) | (adcChannel<SBIT_CHS0);  //select required channel and turn ON adc

    delay(1000);                   //Acquisition Time(Wait for Charged Hold Capacitor to get charged )
   
    GO=1;                           // Start ADC conversion
    while(GO_DONE==1);              // Wait for the conversion to complete
                                    // GO_DONE bit will be cleared once conversion is complete

    return((ADRESH<<8) + ADRESL);   // return right justified 10-bit result
 }


int main()
{
    int adcValue=0;
    
    TRISB = 0x00; // Configure PORTB and PORTD as output to display the ADC values on LEDs
    TRISD = 0x00;
    

    ADC_Init();             //Initialize the ADC module

    while(1)
    {
        adcValue = ADC_Read(0);       // Read the ADC value of channel zero
        
        PORTB = (adcValue & 0xff);    //Adc value displayed on LEDs connected to PORTB,PORTD
        PORTD = (adcValue>>8) & 0x03; // PORTB will display lower 8-bits and PORTD higher 2-bits
    }
}