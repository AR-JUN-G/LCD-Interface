#include "lcd.h"

int main()
{
    initAll();
    lcdWriteString("hello all");
    _delay_us(100);
    return 0;
}