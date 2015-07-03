/* 
 * File:   main.c
 * Author: David Manouchehri
 *
 * Created on March 26, 2014, 5:48 AM
 */

#include <hardware.h> // Reminder, ADC is set to 10 bits, NOT 8
#use pwm (OUTPUT = PIN_C2, FREQUENCY = 32kHz, DUTY=10)
//#include <bcd.c>
//#include <nju6355new.c>
#include <stdlib.h>
#include <input.c>
#include <utility.c>

//Temp pin change



//#include <ds1631.c>

/*
 * 
 */
void main(void)
{
    //int count = 1, i;
    //float value = 0;
    //setupLCD();
    //init_temp();

    //int count=0;
    //int hour, min, sec, last_sec;
    //rtc_init ();
    //set_time ();
    setupLCD(); 

    while(1)
    {
        /*rtc_get_time (hour, min, sec );
        if ( sec!=last_sec)
        {
            printf ( "\n\r" );
            printf ( " %c%c:%c%c:%c%c ", display_first_bcd ( hour),
            display_second_bcd (hour),
            display_first_bcd (min), display_second_bcd (min),
            display_first_bcd (sec), display_second_bcd (sec) );
            
            //LCD
            printf ( putcharLCD, "\r%c%c:%c%c:%c%c ", display_first_bcd ( hour),
            display_second_bcd (hour),
            display_first_bcd (min), display_second_bcd (min),
            display_first_bcd (sec), display_second_bcd (sec) );
            
            last_sec = sec;
        } // end if
        if ( kbhit() && ( getc() == 'S' ))
        {
            set_time();
        }*/
        printf ( putcharLCD, "Hi\r\n");
        delay_ms(100);
        /*Old
        value = read_full_temp ();
        value /= 100.0;

        if(value <= 75)
        {
            flipLED(0);
        }
        else if(value >= 80)
        {
            flipLED(2);
        }
        else
        {
            flipLED(1);
        }

        printf ( putcharLCD, "\rTemp is %4.2f\n", value );
        printf ( putcharLCD, "Manouchehri" );
        printf("Temperature is %4.2f\r\n", value);

        for(int i = 0; i < 100; i++)
        {
            displayNumber(value);
        }
        */
    }
}