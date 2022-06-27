#include<avr/io.h>
#include<util/delay.h>

#define LCDDDR DDRA
#define CONTROLDDR DDRB
#define lcdPort PORTA
#define controlPort PORTB
#define EN PB2
#define RW PB1
#define RS PB0



void enablePulse()
{
    controlPort |=(1<<EN);
    _delay_us(2);
    controlPort &=~(1<<EN);
}



void lcdWriteCommand(uint8_t cmd)
{
    lcdPort =(cmd);
    controlPort &=~(1<<RW);
    controlPort &=~(1<<RS);
    enablePulse();  ////give high to low pulse
    if(cmd == 0x01 || cmd ==0x02)
    {
        _delay_us(2000);
    }
    else{
        _delay_us(100);
    }
}

void lcdWriteData(uint8_t data)
{
    lcdPort =(data);
    controlPort &=~(1<<RW);
    controlPort |=(1<<RS);
    enablePulse();  ////give high to low pulse
    _delay_us(50);
}

void lcdWriteChar(const char ch)
{
    lcdWriteData(ch);
    _delay_us(80);
}

void lcdWriteString(const char *str) ///const 
{
    while(*str)
    {
            lcdWriteData(*str);
            str++;
            _delay_us(80);
    }
}

void lcdInit()
{
    //8bit mode
    lcdWriteCommand(0x38);

    ///clear Display
    lcdWriteCommand(0x01);

    ///return home
    lcdWriteCommand(0x02);

    ///make increment in the cursor 
    //lcdWriteCommand(0x06);

    //lcdWriteCommand(0X80);
    
}

void lcdGoto(uint8_t byte,uint8_t line)
{
    uint8_t command =(1<<7);
    if(line==1)
    {
        byte+=40;
    }
    command +=byte;
    lcdWriteCommand(command);
}


int main()
{
    _delay_ms(100);

    LCDDDR =0xFF;
    lcdPort=0X00;
    CONTROLDDR |=(1<<EN) | (1<<RW) | (1<<RS);
    controlPort =0x00;
    
    
    lcdInit();
    lcdWriteString("Hello ALL");


}
