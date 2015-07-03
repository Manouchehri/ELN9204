/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to inputs
*/
#include <16F877A.h>
#fuses HS, NOLVP, NOWDT, PUT
#use delay (clock = 20000000)
#use rs232 (baud=9600, xmit=PIN_C6, rcv=PIN_C7)

#define greenLED PIN_A5
#define yellowLED PIN_B4
#define redLED PIN_B5
#define push PIN_A4

//Declare Functions
void delaySeconds (unsigned int delayMs);
void setLED(int);
void clearLEDs (void);
void onePress(void);

void main(void)
{
  int32 count = 0;
  printf("Written by David Manouchehri\n\r");

  while(1)
  {
    setLED(1); //Yellow
    
    onePress();
    clearLEDs();
    setLED(2); //Red

    onePress();
    clearLEDs();
    setLED(0); //Green

    onePress();
    clearLEDs();
    
    //Routine stuff
    printf("Number of runs: %ld\n\r", count);
    count++;    
    //delaySeconds(1);
  }
}
void delaySeconds (unsigned int delayMs)
{
  printf("Delaying for %d seconds\n\r", delayMs);
  delay_ms(delayMs * 1000); 
}

void onePress(void)
{
  while(input(push));
  while(!input(push));
}

void setLED(int select)
{
  switch (select)
  {
    case 0:
    {
      output_low(greenLED);
      printf("Green LED on\n\r");
      break;
    }
    case 1:
    {
      output_low(yellowLED);
      printf("Yellow LED on\n\r");
      break;
    }
    case 2:    
    {
      output_low(redLED);
      printf("Red LED on\n\r");
      break;
    }
  }
}

void clearLEDs(void)
{
  output_high(greenLED);
  output_high(yellowLED);
  output_high(redLED);
  printf("All LEDs cleared\n\r");
}
