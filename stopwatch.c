
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define RST 0
#define LCDDDR DDRA
#define CONTROLDDR DDRB
#define lcdPort PORTA
#define controlPort PORTB
#define EN PB2
#define RW PB1
#define RS PB0
#define DEBOUNCE_TIME 25 ///Avoid Debouncing

#define RESET_BUTTON_DURATION 1000 // duration press of a button to timer reset



static const unsigned char digits[10][14] =
{
	{ 0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F},   // 0
	{ 0x04, 0x06, 0x06, 0xFF, 0xFF, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0},   // 1
	{ 0x0E, 0x07, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0xE0, 0xF0, 0xD8, 0xCC, 0xC6, 0xC3, 0xC1},   // 2
	{ 0x0E, 0x07, 0x03, 0xC3, 0xC3, 0xFF, 0x7E, 0x70, 0xE0, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F},   // 3
	{ 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF},   // 4
	{ 0x7E, 0xFF, 0xC3, 0xC3, 0xC3, 0xC7, 0x8E, 0x70, 0xE0, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F},   // 5
	{ 0xFE, 0xFF, 0xC3, 0xC3, 0xC3, 0xC7, 0x8E, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F},   // 6
	{ 0x0E, 0x07, 0x03, 0x03, 0xE3, 0xFF, 0x1E, 0x00, 0xE0, 0xF8, 0x1F, 0x07, 0x00, 0x00},   // 7
	{ 0x3E, 0xFF, 0xC3, 0xC3, 0xC3, 0xFF, 0x3E, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F},   // 8
	{ 0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0x71, 0xE3, 0xC3, 0xC3, 0xC3, 0xFF, 0x7F},   // 9
};

uint16_t ms; // millisecond counter
uint8_t sec; // second counter
uint8_t min; // minute counter
uint8_t hr; // hour counter

uint16_t ms_button; // duration press of a button

uint8_t state_button = 1; // timer state: 0-reset; 1-paused; 2-continues to count


void Display_Reset()
{
	PORTB &= ~(1<<RST);
	_delay_ms(100);
	PORTB |= (1<<RST);
}

//Command write function
void lcdWriteCommand(uint8_t cmd)
{
    lcdPort =(cmd);
    controlPort &=~(1<<RW);
    controlPort &=~(1<<RS);
    enablePulse();  ////give high to low pulse
    if(cmd == 0x01 || cmd ==0x02)
    {
        _delay_us(1530);
    }
    else{
        _delay_us(100);
    }
}


//Initialization of Display
void Display_init()
{
	Display_Reset();  // reset the display
	lcdWriteCommand(0x20);  // command set in basic mode
	lcdWriteCommand(0x0C);  // display result in normal mode
}

// Clear the Display
void Display_Clear()
{
	PORTB |=(1<<EN)
	for (int k=0; k<=503; k++)
    {	
        lcdWriteCommand(0x00);
    }
	PORTB &= ~(1<<EN);
}

unsigned char button_state()
{
	/* the button is pressed when BUTTON bit is clear */
	if (!(PINC & (1<<BUTTON)))
	{
		_delay_ms(DEBOUNCE_TIME);

		if (!(PINC & (1<<BUTTON))) 
    {
        return 1;
    }
	}
	return 0;
}

// initialize timer1, interrupt and variable
void timer1_init()
{
	// set up timer with prescaler = 256 and CTC mode
	TCCR1B |= (1 << WGM12)|(1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	// initialize compare value
	OCR1A = 625;
	
	// enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	// enable global interrupts
	sei();
}
	




int main(void)
{
	Port_Init(); // Port Initialization
	
	
	Display_init(); // Display initialization
	Display_Clear(); // Display clear
	
	// Timer1 Initialization 
	timer1_init();

    
	// Loop forever
	while(1)
	{
		
    }
}
