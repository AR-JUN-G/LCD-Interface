#include <avr/io.h>




void adcConversion()
{
    /////ENABLING THE ADC CONVERSION /////
    ADCSRA|=(1<<ADEN);

    ////// REFERENCE VOLTAGE AS 5V /////
    ADMUX &=~(1<<REFS0);
    ADMUX &=~(1<<REFS1);

    /////PRESCALAR 8 /////
    ADCSRA |=(1<<ADPS1);
    ADCSRA |=(1<<ADPS0);

    ///PA5-MISO///
    ADMUX |=(1<<MUX0);
    ADMUX |=(1<<MUX2);

    while(!((ADCSRA>>ADIF)&1))
    {
        ////WILL RUN UNTIL CONVERSION IS DONE /////
    }
    ADCSRA |=(1<< ADIF);// WRITING 1 CAN CLEAR ADIF 
    ///USED TO DO  REPEATED VALUES ///
    ////READING THE INPUT
    x=(ADCH<<8)|ADCL;
}

int main()
{
    
}