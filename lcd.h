////////////////////INTERFACING LCD (16*2) USING ATTINY84A WITH SHIFT REGISTER(SN74HC595)///////////////////
/////AUTHOR: ARJUN ////

#ifndef lcd_h
#define lcd_h


///////////////     HEADER //////////////////
#include <avr/io.h>
#include <util/delay.h>

///////////////////////////////////////// MACROS  /////////////////////////////////////////////////

//////  SHIFT REGISTER   //////////
#define clockPin PA0
#define latchPin PA1
#define dataPin  PA2
#define clrpin PA3

///LCD MACRO //////////////////
#define RS PB0
#define EN PB2

//// LCD COMMAND
#define clearDisplay 0x01
#define returnHome 0x02
#define cursorRight 0x06
#define cursorLeft 0x04
#define displayOn 0x0F
#define bitMode8 0x3C //8 BITMODE & 2 LINE MODE & 5*11 MODE
#define bitMode4 0x20 //4 BITMODE & 1 LINE MODE & 5*8 MODE
///////////////////////////////////////////////////////////////////

//////////// PROVIDE A  PULSE TO STORE THE VALUE IN THE LCD /////
void enablePulse();
//////////// PROVIDE A HIGHPULSE  //////////////////////
void highDataPin();
///////////// PROVIDE A LOWPULSE //////////////////////
void lowDataPin();

void clr();
///////////// PASS DATA FROM ATTINY TO SN74HC595 IN SERIAL/////////////////
void writeSr(uint8_t data);
//////////// CONFIG THE LCD TO WRITE THE COMMAND ///////////////
void writeCommand (uint8_t cmd);
/////////// CONFIG THE LCD TO WRITE THE DATA IN LCD ////////
void writeData(uint8_t data);
//////////  WRITE THE STRING IN THE LCD DISPLAY /////////
void lcdWriteString(const char *str);
////////// PRINTS THE INTEGER IN THE LCD DISPLAY /////////
void lcdPrintInt(int n);
////////// INTIALIZE ALL THE NECESSARY COMMANDS
void initAll();
///////////////////////////////////////////////////////////////

#endif