#include <16F887.h>
#fuses INTRC_IO, NOLVP, NOWDT, PUT
#use delay (clock = 8MHz)
#use rs232 (baud=9600, xmit=PIN_C6, rcv=PIN_C7)

#define greenLED PIN_A5
#define yellowLED PIN_B4
#define redLED PIN_B5
#define push PIN_A4
#define greenLEDext PIN_E0
#define yellowLEDext PIN_E2
#define redLEDext PIN_A2
#define LCD_E PIN_B5
#define LCD_RS PIN_B4
#define display1 PIN_B0
#define display2 PIN_B1
#define DAL_SCL PIN_C3
#define DAL_SDA PIN_E1