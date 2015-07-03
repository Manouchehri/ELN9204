/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to ADC
*/
#include <hardware.h>
#include <utility.c>
#include <stdlib.h>
#include <input.c>

struct animal
{
  char code;
  char species[8];
  int count;
};

#define max 3

struct animal animals[max] = 
{
  {'A',"Ant",0},
  {'B',"Bird",0},
  {'C',"Cat",0}
};

int find(char code, int & index)
{
  for(index = 0; index < MAX; index++)
  {
    if(animals[index].code == code)
      return(true);
  }
  return(false);
}

void main(void)
{
  int32 county = 0;
  //long a, b, result; 
  //char opr;
  int index;
  char code;

  printf("Written by David Manouchehri\n\r");

  while(1)
  { 
    printf("\r\nEnter the code (A, B, C):");
    code = getc();
    printf("\r\n");
    
    if(find(code,index))
    {
      animals[index].count++;
      printf("You now have %u %s's\r\n", animals[index].count, animals[index].species);
    }
    else
    {
      printf("Not a valid\r\n");
    }

    //printf("\n\r%ld", a);
    //onePress();
    //delay_ms(100);
    //flipLED(0);
    //Routine stuff
    printf("Number of runs: %ld\n\r", county);
    county++;    
    //delay_ms(100);
  }
}
