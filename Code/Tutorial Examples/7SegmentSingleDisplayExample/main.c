#include <pic16f877a.h>

void DELAY_ms(unsigned int ms_Count)
{
    unsigned int i,j;
    for(i=0;i<ms_Count;i++)
    {
        for(j=0;j<1000;j++);
    }
}


int main() {
    char seg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
    int i;

    /* Configure the ports as output */
    TRISD = 0x00;

    while (1) 
    {
        for (i = 0; i <= 9; i++) // loop to display 0-9
        {
            PORTD = seg_code[i]; 
            DELAY_ms(1000);
        }
    }
}