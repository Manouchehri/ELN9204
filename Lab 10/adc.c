/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to ADC
*/
#include <hardware.h>
#include <utility.c>
#include <stdlib.h>
#include <input.c>

void main(void)
{
  int32 count = 0;
  long a, b, result; 
  char opr;

  printf("Written by David Manouchehri\n\r");

  while(1)
  {
    printf("Enter the number\n\r");
    a = get_long();

    printf("\n\rIs the number in celsius (1) or fahrenheit (2)?\n\r");

    opr = getc();
    switch(opr)
    {
      case '1' :
        result = a*1.8 + 32;
        printf("%ld F\r\n", result);
        break;
      case '2' :
        result = (a - 32)/1.8;
        printf("%ld C\r\n", result);
        break;
    }

    printf("Number of runs: %ld\n\r", count);
    count++;    
  }
}
