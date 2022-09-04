#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>


void highDataPin()
{
    PORTA|=(1<<dataPin);   ///// make high when the input is one
}

void lowDataPin()
{
    PORTA&=~(1<<dataPin);  /// make low when the input is zero
}

void enablePulse(){
	PORTB &=~(1<<EN);
	_delay_ms(1);
	PORTB |=(1<<EN);
}

void clr()
{
    PORTA |=(1<<clockPin);
    PORTB |=(1<<clrpin);
    PORTB&=~(1<<clrpin);
    PORTA &=~(1<<clockPin);

}

void writeCommand (uint8_t cmd)
{
	PORTB &=~(1<<RS);
	//PORTA =cmd;
    writeSr(cmd);
	enablePulse();
    //if(cmd==0x01 || cmd ==0x02)
	if(cmd == 0b00000001 || cmd ==0b00000010)
    {
      _delay_us(2000); 
    }
    else{
      _delay_us(100);
    }

}



void writeData(uint8_t data)
{
	PORTB |=(1<<RS);
	//PORTA =data;
    writeSr(data);
	enablePulse();
	_delay_us(100);

}

void lcdWriteString(const char *str) ///const 
{
    while(*str)
    {
            writeData(*str);
            str++;
           _delay_ms(80);
    }
}

void lcdPrintInt(int n){
	if(n<0){
		writeData('-');
		n*=-1;
	}
	int x = 10000;
	while(!(n/x)){
		x/=10;
		if(x==0){
			writeData('0');
			return;
		}
	}
	while(x>0){
		writeData('0'+n/x);
		n = n%x;
		x/=10;
	}
}

//////////      shift register    ///////////////
void writeSr(uint8_t data)
{
        uint8_t pattern =data;
        PORTA &=~(1<<latchPin);     ////MAKING OUTPUT CLOCK ZERO(STORAGE CLOCK) DISABLE THE OUTPUT

    for(int j=0;j<9;j++)
        {
        PORTA|=(1<<clockPin);      ////SET THE SHIFT REGISTER CLOCK(SRCLOCK)
        if(pattern & 0b10000000)
        {
            highDataPin();
        }
        else
        {
            lowDataPin();
        }
        pattern=pattern<<1;
        PORTA&=~(1<<clockPin);  //// LOW THE SHIFT REGISTER CLOCK 
        }
        PORTA|=(1<<latchPin);   ///SETTING THE LATCH CLOCK TO ENABLE THE OUTPUT
        _delay_us(100);
}


void initAll()
{
    ///CONFIGURING AS OUTPUT PIN
     DDRA |=(1<< clockPin | 1<< latchPin| 1<< dataPin);  
     DDRB  =0xff;
     PORTA =0x00;
     PORTB =0x00;
     PORTB &=~(1<<clrpin);
     PORTB |=(1<<clrpin);

     ////8 bit mode
	writeCommand(bitMode8);//14

	////LCD ON CURSOR ON CURSOR BLINKING ON
	writeCommand(displayOn);//15

	////LCD CURSOR POSITION
	writeCommand(0X1C);//28

	////CLEARING THE DISPLAY
	writeCommand(clearDisplay));//1

}
