/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to ADC
*/
#include <hardware.h>
#include <utility.c>
//#include <stdlib.h>
//#include <input.c>

int32 overflowCount;

#int_timer1
void addOverflow(void)
{
  overflowCount++;
}

void main(void)
{
  int32 county = 0;

  int32 time;

  setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
  enable_interrupts(int_timer1);

  printf("Written by David Manouchehri\n\r");
  
  

  while(1)
  {
    enable_interrupts(global);

    while(input(push));
    set_timer1(0);
    overflowCount = 0;

    while(!input(push));
    disable_interrupts(global);
    time = get_timer1();
    time = time + (overflowCount * 65536);
    time -= 15;

    printf("Time is %lu.%06lu seconds.\r\n", time/5000000, (time%5000000)/5);

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
