/*
Author: David Manouchehri (d@32t.ca)

Program Description:
How to use include files
*/
#include <hardware.h>
#include <utility.c>

void main(void)
{
  int32 count = 0;
  printf("Written by David Manouchehri\n\r");
  
  while(1)
  { 
    signed int i;
    for (i = 7; i >= 0; i--) 
    {
      printf("i is %d\n\r", i);
      binaryLEDs(i);
      delaySeconds(2);
    }
  
    //Routine stuff
    printf("Number of runs: %ld\n\r", count);
    count++;    
    //delaySeconds(1);
  }
}
