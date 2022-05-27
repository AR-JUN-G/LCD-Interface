#include<avr/io.h>
#include<util/delay.h>

#define RS 0
#define en 2


void sendCommand(unsigned char command)
{
    PORTA=command;
    //////////GIVING COMMAND
    PORTB&=~(1<<RS);
    PORTB|=(1<<en);
    //////////////
    _delay_ms(50);

}


void sendCharacter(unsigned char character)
{
    PORTA  =(character);
    PORTB |=(1<<RS);
    PORTB |=(1<<en);
    _delay_ms(50);
    PORTB  &=~(1<<en);
    /////clearing the command
    PORTA=0;
}

int main()
{
    /////SETTING AS OUTPUT PINS
    DDRA |=(0XFF);
    DDRB|=(1<<PB0);
    DDRB|=(1<<PB1);
    DDRB|=(1<<PB2);
    _delay_ms(50);

    sendCommand(0X01);////clear screen
    sendCharacter(0X38);////16*2 lcd mode
    sendCharacter(0x0E);///screen and cursor on

    ////sending the character 
    sendCharacter(0x56);
    sendCharacter(0x45);
    sendCharacter(0x53);
    ////
}