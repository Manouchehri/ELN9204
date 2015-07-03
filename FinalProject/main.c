/* 
 * File:   main.c
 * Author: David Manouchehri
 *
 * Created on April 3, 2014, 9:24 PM
 */

#include "config.h" /*All the pins are set in here*/
#include "lcd.c"
#include "ds1631.c"
#include "nju6355.c"
/*
 * 
 */

/*Setup variables and set to default vaules*/
float tempValue = 0;
unsigned int16 reading = 0;
unsigned int16 light = 0;
unsigned int8 brightness = 100; /*Decent default value, in the future it could easily be adjustable*/
float voltage = 0;
float current = 0;
int hour, min, sec;
int1 configView = 0;
int1 errorBit = 0;

/*Basic IO setup, nothing too fancy.*/
void setupIO(void)
{
    LCD_E = LCD_E0; /*Use LCD#1*/
    setupLCD();
    LCD_E = LCD_E1; /*Use LCD#2*/
    setupLCD();

    SETUP_ADC(ADC_CLOCK_INTERNAL);
    setup_adc_ports(sAN0 | sAN1 | sAN2);

    init_temp();
    rtc_init();

    pwm_set_duty_percent(brightness); /*Brightness setting, from a scale of 0 to 1000; a lower value makes the screens darker*/
}

/*This gets both the voltage and current through the resistor network*/
void getBattery(void)
{
    set_adc_channel(0);
    delay_us(10);
    reading = read_adc();
    voltage = (float)reading * 1000.0 / 1024.0 / 35.0 ; /*Cast to avoid rounding*/

    set_adc_channel(1);
    delay_us(10);
    reading = read_adc();
    current = (float)reading * 1000.0 / 1024.0; /*Because of the 10-bit ADC, scaling the current is quite easy; even without the scaling it's pretty accurate*/
}

void getTime(void)
{
    rtc_get_time(hour, min, sec);
    hour = rtc_rm_bcd(hour); /*This is needed to convert the value to BCD*/
    min = rtc_rm_bcd(min);
    /*Oddly enough seconds are handled differently than minutes and hours. No clue why, I'll probably have to look into the library later*/
}
void getTemp(void)
{
    tempValue = read_full_temp ();
    tempValue /= 100.0; /*Scale it down, and the .0 is there to avoid rounding*/
}

/*This function could be used later on for displaying warnings if the light gets too dark*/
void getLight(void)
{
    set_adc_channel(2);
    delay_us(10);
    light = read_adc();
}

/*This is more or less the body of the program*/
void routineUpdate(void)
{
    getBattery();
    LCD_E = LCD_E1;
    printf(putcharLCD, "\f%4.2fV-%4.2fmA  ", voltage, current);
    if(!configView) /*Use both LCD screens*/
    {
        getTime();
        if((voltage > 10 && !errorBit) || errorBit) /*The !errorbit isn't actually needed, but I like having it there for reading*/
        {
            printf(putcharLCD, "\n%d:%d:%d BADCLRERR  ", hour, min, sec);
            output_high(LED3);
            output_low(LED1);
            output_low(RELAY);
            errorBit = 1;
        }
        else
        {
            printf(putcharLCD, "\n%d:%d:%d GOOD     ", hour, min, sec);
            output_high(LED1);
            output_low(LED3);
            output_high(RELAY);
        }

        LCD_E = LCD_E0;
        getLight();
        printf(putcharLCD, "\fL:%4.2f%%", light * 1000.0 / 1024.0 / 10);
        
        getTemp();
        printf(putcharLCD, " T:%4.2f", tempValue);
        printf(putcharLCD, "\nPB1 for config  ");
    }
    else /*Only use one LCD screen, leave the other one alone for the config menu*/
    {
        getTime();
        getTemp();
        printf(putcharLCD, "\n%4.2f %d:%d:%d", tempValue, hour, min, sec);
        LCD_E = LCD_E0;
    }
}

/*This is probably the most confusing function to read through. Basically, it allows the user to adjust the current time*/
int getTimePB(char unit)
{
    configView = 1; /*This automatically turns off one of the LCD screens for us later on in routineUpdate()*/
    unsigned int8 time = 0;
    unsigned int8 range = 0;
    int1 blocking = 0;
    getTime(); /*Update the current time to BCD before we start working with it*/

    switch(unit) /*At the moment I'm just doing hours and minutes, but this makes it pretty easy to add anything else later on*/
    {
        case 'h':
            range = 23;
            time = hour;
            break;
        case 'm':
            range = 59;
            time = min;
            break;
        default:
            range = 0; /*Throwing a compiler error would be a good idea to add*/
    }
    printf(putcharLCD, "\nthen PB1: %d     ", time); /*Give the current value to the user*/
    while(input(PB1)) /*Wait until the set button is released*/
    {
        if(!blocking) /*Don't run again unless the button has been released.*/
        {
            if(!input(PB2)) /*If it's pressed*/
            {
                if(time < range)
                {
                    time++;
                }
                else
                {
                    time = 0;
                }
                blocking = 1;
                printf(putcharLCD, "\nthen PB1: %d     ", time); /*Bit of a hack, I should manually set the location with the LCD. This wastes a few extra clock cycles*/
            }
        }
        else
        {
            if(input(PB2)) /*Released, unblock*/
            {
                blocking = 0;
            }
        }
        routineUpdate(); /*Just because we're at the config menu doesn't mean I want everything to freeze up!*/
    }
    return time; /*Gives back whatever value the user set*/
}
void setTime(void)
{
    hour = rtc_get_bcd(hour);
    min = rtc_get_bcd(min);
    rtc_set_datetime (0, 0, 0, 0, hour, min); /*Just focusing on hours and minutes here. Too bad seconds aren't adjustable in the stock library*/
}
void configMenu(void)
{
    /*Menu checking and setting*/
    if(!input(PB1) && configView == 0)
    {
        while(!input(PB1)) /*Prevents blocking and some other nasty bugs*/
        {
            routineUpdate();
        }
        configView = 1; /*In short, we don't want to go to the config menu UNTIL the user releases the button*/
        routineUpdate();

        LCD_E = LCD_E0;
        printf(putcharLCD, "\rHour with PB2, ");
        hour = getTimePB('h');
        setTime();

        /*More blocking*/
        if(input(PB1))
        {
            routineUpdate();
        }

        printf(putcharLCD, "\rMinute with PB2, ");
        min = getTimePB('m');
        setTime();

        if(input(PB1))
        {
            routineUpdate();
        }
    }
    configView = 0;
}
void main(void)
{
    setupIO();

    output_high(RELAY); /*We need the relay on to begin with*/

    /*Another option would be to force the user to set the time to start with. Personally I like having it default to 0:0:0*/
    hour = 0;
    min = 0;

    setTime();

    while(1)
    {
        routineUpdate(); /*Assuming nothing interesting is happening, this gets run*/
        configMenu(); /*Just check, may or may not run*/
        if(!input(PB1) || !input(PB2))
        {
            errorBit = 0; /*Shut the error off, check the voltage again*/
        }
    }
}

