/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Play with if commands?
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
  int value1 = 3;
  int value2 = 5;
  int sum;
  sum = value1 + value2;

  printf("Written by David Manouchehri\n\r");

  while(1)
  {
    //delaySeconds(2);
    //output_high(greenLED);
    //output_low(greenLED);
    //sum = value1 + value2;
    if(sum == 0)
    {
      printf("Sum is equal to %d\n\r", sum);
      sum = value1 + value2;
    }
    else
    {
      printf("Sum is equal to %d\n\r", sum);
      sum--;
    }

    printf("Number of runs: %d\n\r", count);
    count++;    
    delaySeconds(1);
  }
}

void delaySeconds (unsigned int delayMs)
{
  printf("Delaying for %d seconds\n\r", delayMs);
  delay_ms(delayMs * 1000); 
}
