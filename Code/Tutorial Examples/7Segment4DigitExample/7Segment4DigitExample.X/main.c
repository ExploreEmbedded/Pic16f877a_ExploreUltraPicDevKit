#include <pic16f877a.h>

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08	

void DELAY_ms(unsigned int ms_Count)
{
    unsigned int i,j;
    for(i=0;i<ms_Count;i++)
    {
        for(j=0;j<1000;j++);
    }
}



int main() {
    char seg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
    int cnt, num, temp,i;

    /* Configure the ports as output */
    TRISB = 0x00; // Data lines
    TRISD = 0x00; // Control signal PORTD0-PORTD3

    while (1) 
    {
        for (cnt = 0x00; cnt <= 9999; cnt++) // loop to display 0-9999
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