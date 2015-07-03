/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to ADC
*/
#include <hardware.h>
#include <stdlib.h>
#use rs232 (baud=9600, xmit=PIN_C6, rcv=PIN_C7)

void main(void)
{
  long time;
  float a, b, c;
  a = 5;
  b = 100;

  setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
  set_timer1(0);
  
  c = a * b;

  //printf("test");


  time = get_timer1();
  time -= 2;
  printf("\r\n The program takes %lu clock cycles", time);
  printf("\r\n Each clock cycle is %lu microseconds \r\n", (time+2)/5);
  printf("\r\n Total time is %lu microseconds \r\n", time * (time+2)/5);
}
