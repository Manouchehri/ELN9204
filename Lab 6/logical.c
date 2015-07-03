/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Math stuff
*/
#include <hardware.h>
#include <utility.c>

void main(void)
{
  int32 count = 0;
  int A = 1; 
  int B = 2;
  
  printf("Written by David Manouchehri\n\r");
    
  printf("A is %d, B is %d\n\r", A, B);
  printf("A + B = %d\n\r", A + B);
  printf("A * B = %d\n\r", A * B);
  printf("A / B = %d with remainder %d\n\r", A / B, A % B);
  printf("A AND B = %d\n\r", A & B);
  printf("A NOR B = %d\n\r", A ^ B);

  /*while(1)
  {
    
 
    //Routine stuff
    printf("Number of runs: %ld\n\r", count);
    count++;    
    //delaySeconds(1);
  }*/
}
