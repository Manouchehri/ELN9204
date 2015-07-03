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
  unsigned long int reading;
  float readingVolts;
   
  printf("Written by David Manouchehri\n\r");

  setup_adc_ports(RA0_ANALOG);
  setup_adc(ADC_CLOCK_INTERNAL);

  set_adc_channel(0);
  delay_us(10);

  while(1)
  {
    reading = read_adc();
    readingVolts = (reading * 5.0)/255;
    delay_us(10);

    printf("Reading is %lu = %4.2f Volts (float)\r\n", reading, readingVolts);
    
    if(readingVolts > 3.3)
    {
      clearLEDs();
      setLED(1);
    }
    else if(readingVolts > 1.6)
    {
      clearLEDs();
      setLED(2);
    }
    else
    {
      clearLEDs();
      setLED(0);
    }
    
 
    //Routine stuff
    printf("Number of runs: %ld\n\r", count);
    count++;    
    delay_ms(100);
  }
}
