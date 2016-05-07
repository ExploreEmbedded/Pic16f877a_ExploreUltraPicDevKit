#include <pic16f877a.h>

void DELAY_ms(unsigned int ms_Count)
{
    unsigned int i,j;
    for(i=0;i<ms_Count;i++)
    {
        for(j=0;j<1000;j++);
    }
}

int main() 
{
  /* Configure all the ports as Output */
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00; 
    
    while(1)
    {
        PORTA = 0xff; /* Turn ON all the leds connected to Ports */
        PORTB = 0xff;
        PORTC = 0xff;
        PORTD = 0xff;
        DELAY_ms(100);
        
        PORTA = 0x00; /* Turn OFF all the leds connected to Ports */
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;
        DELAY_ms(100);
    }

    return (0);
}