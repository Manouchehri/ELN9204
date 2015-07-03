/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Turn the green LED on and off at set intervals and sent the delay time over RS232
*/
#include <16F877A.h>
#fuses HS, NOLVP, NOWDT, PUT
#use delay (clock = 20000000)
#use rs232 (baud=9600, xmit=PIN_C6, rcv=PIN_C7)

#define greenLED PIN_A5

//Declare Functions
void delaySeconds (unsigned int delayMs);

void main(void)
{
  int count = 0;
  printf("Written by David Manouchehri\n\r");

  while(1)
  {
    /*output_low(greenLED); //LED is active low
    delaySeconds(7);
    output_high(greenLED);
    delaySeconds(7);*/
    
    output_low(greenLED);
    delaySeconds(2);
    output_high(greenLED);
    delaySeconds(2);
    output_low(greenLED);
    delaySeconds(5);
      
    printf("Count is %d\n\r", count);
    count++;    
  }
}

void delaySeconds (unsigned int delayMs)
{
  printf("Delaying for %d seconds\n\r", delayMs);
  delay_ms(delayMs * 1000); 
}
