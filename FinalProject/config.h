/* 
 * File:   config.h
 * Author: David Manouchehri
 *
 * Created on April 11, 2014, 4:39 PM
 */

#include <16F887.h>
#device ADC = 10 /*Use a 10-bit ADC instead of 8-bit*/
#fuses INTRC_IO, NOLVP, NOWDT, PUT /*Use internal clock*/

/*Define general I/O*/
#define LED1 PIN_C0
#define LED2 PIN_A4
#define LED3 PIN_A5
#define RELAY PIN_E0
#define PB2 PIN_C3
#define PB1 PIN_C4

/*Define pins for LCD*/
#define LCD_E0 PIN_C5
#define LCD_E1 PIN_B5
#define LCD_RS PIN_B4

/*Define pins for 6355*/
#define RTC_DATA PIN_B3
#define RTC_CLK PIN_B2
#define RTC_CE PIN_B1
#define RTC_IO PIN_B0

/*Define pins for 1631*/
#define DAL_SDA PIN_E1
#define DAL_SCL PIN_E2

#use delay (clock = 8MHz) /*Can be adjusted to anything below 8MHz with the internal clock*/
/*#use rs232 (baud=9600, xmit=PIN_C6, rcv=PIN_C7)*/ /*RS232 isn't really needed at the moment for anything; I've got the pushbuttons and LCDs doing all of the work*/
#use pwm (OUTPUT = PIN_C2, FREQUENCY = 32kHz, DUTY=50) /*Used for brightness*/
