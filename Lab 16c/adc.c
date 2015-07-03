/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to PWM
*/
#include <hardware.h> // Reminder, ADC is set to 10 bits, NOT 8
#include <utility.c>
#include <stdlib.h>
#include <input.c>

#USE PWM(OUTPUT=PIN_C2, PERIOD=20us)

void main(void)
{
  pwm_on(); // Turn it off until we're ready
  setup_adc(ADC_CLOCK_INTERNAL);
  setup_adc_ports(ALL_ANALOG);
  set_adc_channel(0);
  delay_us(10);  

  int16 currentDuty = 0;
  int16 nextDuty = null;
  int16 lightSensor = null;
  int1 motorPower = 1; // Set to 0 to shut off
  int1 currentPower = 0;
  int1 direction = 0; // 0 is forward, 1 is reverse
  int16 deadzone = 5; // Set to as small as possible
  printf("Written by David Manouchehri\n\r");

  while(1)
  {
    set_adc_channel(0);
    delay_us(10);
    int16 nextDuty = read_adc();
    delay_us(10);    

    set_adc_channel(1);
    delay_us(10);
    int16 lightSensor = read_adc();
    //printf("Light: %lu\r\n", lightSensor);
    delay_us(10);

    if(lightSensor < 700)
    {
      motorPower = 0;
      setLED(0, 0);
    }
    else
    {
      motorPower = 1;
      setLED(0, 1);
    }
    
    // The reading can go up to 1023, while the duty will max out at only 1000, so this adjusts the value slightly
    nextDuty = (long long)nextDuty * 1000 / 1023;

    if(motorPower)
    {
      pwm_set_duty_percent(nextDuty);
    }
    else
    {
      pwm_set_duty_percent(0);
    }

    // This is for reversing the motor
    if(!input(push))
    {
      onePress(); // Wait until the user releases the button before doing anything
      direction =~ direction; // Flip the bit
      setLED(1, direction);
      if(direction)
        output_high(PIN_C1);
      else
        output_low(PIN_C1);
      printf("Direction is %d (0 is forward, 1 is reverse)\r\n", direction);
    }

    // Only do something if it's outside the deadzone
    //if((currentDuty > (nextDuty + deadzone)) || ( (currentDuty < (nextDuty - deadzone)) && nextDuty > deadzone))
    //{
      //pwm_set_duty_percent(nextDuty);
      //printf("Duty set to %lu\r\n", nextDuty);

      // Just avoiding constantly telling the motor to turn on and off unless it needs to be
      /*if((nextDuty > deadzone && currentDuty < deadzone && motorPower) || (motorPower && !currentPower))
      {
        pwm_on(); // Turn it on if it wasn't on before
        setLED(0, 1); // Green LED on
        currentPower = 1;
        printf("Motor on\r\n");
      }
      //else if((nextDuty < deadzone && currentDuty > deadzone) || (currentPower && !motorPower))
      else if(currentPower && !motorPower)
      {
        pwm_set_duty_percent(0);
        //pwm_off(); 
        setLED(0, 0);
        currentPower = 0;
        printf("Motor off\r\n");
      }*/
      currentDuty = nextDuty; //Done, sync
    //}
  }
}
