#include<avr/io.h>
#include<util/delay.h>

#define RS PB0
#define RW PB1
#define EN PB2
#define lcdPort PORTA

void sendCommand(unsigned char command)
{
    lcdPort =command;
    PORTB &=~(1<<RS);
    PORTB &=~(1<<RW);
    PORTB|=(1<<EN);
    _delay_ms(50);


}

void ledIntIt()
{
    //8bit mode
    sendCommand(0x38);
    _delay_ms(10);
    ///clear Display
    sendCommand(0x01);
    _delay_ms(10);
    ///return home
    sendCommand(0x02);
    _delay_ms(10);
    ///make increment in the cursor 
    sendCommand(0x06);
    _delay_ms(10);

    sendCommand(0X80);
    _delay_ms(10);
    
}

void lcdWrite(unsigned char letters)
{
    lcdPort=letters;
    ////setting lcd in write mode(RW=0) and RS as 1 to write
    PORTB |=(1<<RS);
    PORTB &=~(1<<RW);
    PORTB |=(1<<EN);
    _delay_ms(10);
    PORTB &=~(1<<EN);
}

int main()
{
    DDRA =0Xff;
    DDRB |=(1<<RS);
    DDRB |=(1<<RW);
    DDRB |=(1<<EN);
    ledIntIt();
    _delay_ms(10);
    lcdWrite(0x56);
    _delay_ms(50);
    lcdWrite(0x45);
    lcdWrite(0x53);
    return 0;
}
