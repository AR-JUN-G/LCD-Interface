#include<avr/io.h>
#include<util/delay.h>

#define lcdPort PORTA
#define controlPort PORTB
#define lcdPin PINA
#define EN PB2
#define RW PB1
#define RS PB0



void enablePulse()
{
    controlPort |=(1<<EN);
    _delay_ms(10);
    controlPort &=~(1<<EN);
}



void lcdWriteCommand(unsigned char cmd)
{
    lcdPort =(cmd);
    controlPort &=~(1<<RW);
    controlPort &=~(1<<RS);
    enablePulse();  ////give high to low pulse
}

void lcdWriteData(unsigned char data)
{
    lcdPort =(data);
    controlPort &=~(1<<RW);
    controlPort |=(1<<RS);
    enablePulse();  ////give high to low pulse
}

void lcdWriteChar(unsigned char ch)
{
    lcdWriteData(ch);
}

void lcdWriteString(unsigned char *str)
{
    while(*str)
    {
            lcdWriteData(*str);
            str++;
    }
}

void lcdInit()
{

    //8bit mode
    lcdWriteCommand(0x38);
    _delay_ms(1);

    ///clear Display
    lcdWriteCommand(0x01);
    _delay_ms(1);

    ///return home
    lcdWriteCommand(0x02);
    _delay_ms(1);

    ///make increment in the cursor 
    lcdWriteCommand(0x06);
    _delay_ms(1);

    lcdWriteCommand(0X80);
    _delay_ms(1);
    
}
int main()
{
    
    DDRA |= (1<<PA0);
    DDRA |= (1<<PA1);
    DDRA |= (1<<PA2);
    DDRA |= (1<<PA3);
    DDRA |= (1<<PA4);
    DDRA |= (1<<PA5);
    DDRA |= (1<<PA6);
    DDRA |= (1<<PA7);

    DDRB |= (1<<RW);
    DDRB |= (1<<EN);
    DDRB |= (1<<RS);
    lcdInit();
    lcdWriteString("Hello ALL");
    lcdWriteChar("A");

}
