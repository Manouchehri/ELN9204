#include <16F877A.h>
#fuses HS, NOLVP, NOWDT, PUT
#use delay (clock = 20000000)
#use rs232 (baud=9600, xmit=PIN_C6, rcv=PIN_C7)

#define greenLED PIN_A5
#define yellowLED PIN_B4
#define redLED PIN_B5
#define push PIN_A4
#define greenLEDext PIN_E0
#define yellowLEDext PIN_E2
#define redLEDext PIN_A2