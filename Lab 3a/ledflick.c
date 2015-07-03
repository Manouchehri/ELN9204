/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Turn the green LED on and off at 1 second intervals
*/
#include <16F877A.h>
#fuses HS, NOLVP, NOWDT, PUT
#use delay (clock = 20000000)
#use rs232 (baud=9600, xmit=PIN_C6, rcv=PIN_C7)

#define greenLED PIN_A5

void main(void)
{
  while(1)
  {
    output_low(greenLED); //LED is active low
    delay_ms(2000);
    output_high(greenLED);
    delay_ms(2000);
  }
}
