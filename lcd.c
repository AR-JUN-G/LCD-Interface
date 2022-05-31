#include<avr/io.h>
#include<util/delay.h>

#define lcdPort PORTA
#define controlPort PORTB
#define lcdPin PINA
#define EN PORTB2
#define RW PORTB1
#define RS PORTB0



void enablePulse()
{
    controlPort |=(1<<EN);
    _delay_ms(10);
    controlPort &=~(1<<EN);
}



void lcdWriteCommand(unsigned char cmd)
{
    controlPort &=~(1<<RW);
    controlPort &=~(1<<RS);
    enablePulse();  ////give high to low pulse
    lcdPort =(cmd)|(lcdPin & 0xff);
    enablePulse(); 
    _delay_us(100);
}

void lcdWriteData(unsigned char data)
{
    controlPort &=~(1<<RW);
    controlPort |=(1<<RS);
    enablePulse();  ////give high to low pulse
    lcdPort =(data)|(lcdPin & 0xff);
    enablePulse(); 
    _delay_us(100);
}

void lcdWriteChar(char ch)
{
    lcdWriteData(ch);
}

void lcdWriteString(char *str)
{
    while(*str)
    {
            lcdWriteData(*str);
            str++;
    }
}

void lcdInit()
{
    lcdPort |=1<<PORT0 |1<<PORT1 |1<<PORT2 |1<<PORT3 |1<<PORT4 |
                1<<PORT5 |1<<PORT6 |1<<PORT7 ;
    controlPort |=1<<EN |1<<RS | 1<<RW;
    //8bit mode
    lcdWriteCommand(0x38);
    _delay_ms(10);
    ///clear Display
    lcdWriteCommand(0x01);
    _delay_ms(10);

    ///return home
    lcdWriteCommand(0x02);
    _delay_ms(10);

    ///make increment in the cursor 
    lcdWriteCommand(0x06);
    _delay_ms(10);

    lcdWriteCommand(0X80);
    _delay_ms(10);
    
}
int main()
{
    lcdInit();
    lcdWriteString("Hello ALL");
    lcdWriteData("h");

}
