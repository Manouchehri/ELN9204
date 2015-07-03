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
  unsigned long int reading, average, total;
  float readingVolts;

  unsigned long int history[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

    //printf("Reading is %lu = %4.2f Volts (float)\r\n", reading, readingVolts);
    
    if(readingVolts >= 3.33)
    {
      singleLED(0, 1);
      singleLED(1, 0);
      singleLED(2, 0);
    }
    else if(readingVolts >= 1.66)
    {
      singleLED(1, 1);
      singleLED(0, 0);
      singleLED(2, 0);
    }
    else
    {
      singleLED(2, 1);
      singleLED(0, 0);
      singleLED(1, 0);
    }
    
    //history[9] = 1;
    for (int i = 0; i < 10; i++)
    {
      history[i] = history[i + 1];
    }

    history[9] = reading;

    average = 0;
    for (int j = 0; j < 10; j++)
    {
      average += history[j];
      unsigned long int tempy =  history[j];
      //printf(" %lu ", tempy);
    }
    //printf(" Done\r\n");

    delaySeconds(1);
    
    printf(" %lu ", average);

    /*singleLED(5, 0); 
    singleLED(3, 1);
    delay_ms(reading);
    singleLED(3, 0);
    singleLED(4, 1);
    delay_ms(reading);
    singleLED(4, 0);
    singleLED(5, 1);
    delay_ms(reading);*/

    //delay_ms(100);
    //flipLED(0);
    //Routine stuff
    //printf("Number of runs: %ld\n\r", count);
    count++;    
    //delay_ms(100);
  }
}
