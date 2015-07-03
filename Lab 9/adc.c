/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to ADC
*/
#include <hardware.h>
#include <utility.c>

void main(void)
{
  int32 count = 0;
  printf("Written by David Manouchehri\n\r");

  int currentCount;
  currentCount = read_eeprom(0);
  
  printf("Restore old count: %d\n\r", currentCount);

  while(1)
  {
            
    onePress();

    currentCount++;
    write_eeprom(0, currentCount);
    printf("Count: %d\n\r", currentCount);
    
    //delay_ms(100);
    //flipLED(0);
    //Routine stuff
    //printf("Number of runs: %ld\n\r", count);
    count++;    
    //delay_ms(100);
  }
}
