#include<pic16f877a.h>

/* Configure the data bus and Control bus as per the hardware connection 
   Dtatus bus is connected to PB0:PB7 and control bus PD0:PD2*/
#define LcdDataBus      PORTB
#define LcdControlBus   PORTD

#define LcdDataBusDirnReg   TRISB
#define LcdCtrlBusDirnReg   TRISD

#define LCD_RS     0
#define LCD_RW     1
#define LCD_EN     2


/* local function to generate delay */
void delay(int cnt)
{
    int i;
    for(i=0;i<cnt;i++);
}


/* Function to send the command to LCD */
void Lcd_CmdWrite(char cmd)
{
    LcdDataBus = cmd;               //Send the Command nibble
    LcdControlBus &= ~(1<<LCD_RS);  // Send LOW pulse on RS pin for selecting Command register
    LcdControlBus &= ~(1<<LCD_RW);  // Send LOW pulse on RW pin for Write operation
    LcdControlBus |= (1<<LCD_EN);   // Generate a High-to-low pulse on EN pin
    delay(100);
    LcdControlBus &= ~(1<<LCD_EN); 

    delay(10000);
}



/* Function to send the Data to LCD */
void Lcd_DataWrite(char dat)
{
    LcdDataBus = dat;               //Send the data on DataBus nibble
    LcdControlBus |= (1<<LCD_RS);   // Send HIGH pulse on RS pin for selecting data register
    LcdControlBus &= ~(1<<LCD_RW);  // Send LOW pulse on RW pin for Write operation
    LcdControlBus |= (1<<LCD_EN);   // Generate a High-to-low pulse on EN pin
    delay(100);
    LcdControlBus &= ~(1<<LCD_EN);

    delay(10000);
}



int main()
{
    char i,a[]={"Good morning!"};

    LcdDataBusDirnReg = 0x00;  // Configure all the LCD pins as output
    LcdCtrlBusDirnReg = 0x00;  // Configure the Ctrl pins as output


    Lcd_CmdWrite(0x38);        // enable 5x7 mode for chars 
    Lcd_CmdWrite(0x0E);        // Display OFF, Cursor ON
    Lcd_CmdWrite(0x01);        // Clear Display
    Lcd_CmdWrite(0x80);        // Move the cursor to beginning of first line


    Lcd_DataWrite('H');
    Lcd_DataWrite('e');
    Lcd_DataWrite('l');
    Lcd_DataWrite('l');
    Lcd_DataWrite('o');
    Lcd_DataWrite(' ');
    Lcd_DataWrite('w');
    Lcd_DataWrite('o');
    Lcd_DataWrite('r');
    Lcd_DataWrite('l');
    Lcd_DataWrite('d');

    Lcd_CmdWrite(0xc0);        //Go to Next line and display Good Morning
    for(i=0;a[i]!=0;i++)
    {
        Lcd_DataWrite(a[i]);
    }

    while(1);
}