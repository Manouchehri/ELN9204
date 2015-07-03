/*
Author: David Manouchehri (d@32t.ca)

Program Description:
Intro to ADC
*/
#include <hardware.h>
#include <utility.c>
#include <stdlib.h>
#include <input.c>
#include <9356new.c>

void main(void)
{
  int32 county = 0;

  int cmd, address;

  init_ext_eeprom();

//  count = read_ext_eeprom(0);

  printf("Written by David Manouchehri\n\r");

  while(1)
  {
    printf("\n\n\rEnter address: ");
    address = get_int();

    do
    {
      printf("\n\rRead or write? (R, W): ");
      cmd = toupper(getc());
    }
      while((cmd != 'R') && (cmd != 'W' ));

      if (cmd == 'R')
        printf("\n\rValue is %u", read_ext_eeprom(address));
      else
      {
        printf("\n\rEnter data: ");
        write_ext_eeprom(address, get_int());
      }

    /*printf("LED count: %d\n\r", count);
    binaryLEDs(count);
    onePress();
    count++;
    write_ext_eeprom(0, count);*/
    //printf("\n\r%ld", a);
    //onePress();
    //delay_ms(100);
    //flipLED(0);
    //Routine stuff
//    printf("Number of runs: %ld\n\r", county);
    county++;    
    //delay_ms(100);
  }
}
