void delaySeconds (unsigned int delayMs);
void setLED(int select, int1 setBit);
void clearLEDs (void);
void onePress(void);
void cycleHold(void);
void binaryLEDs (int n);
void debounce(void);
void flip(int1 LED);
void refresh(void);
void singleLED(int LED, int1 set);

int1 currentLEDs[6] = {0, 0, 0, 0, 0, 0};
int1 nextLEDs[6] = {0, 0, 0, 0, 0, 0};

byte CONST LED_MAP[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};

/*void set_time ()
{
    int hour, min;
    printf ( "\r\nHour: " ); hour = get_bcd();
    printf ( "\r\nMin: " ); min = get_bcd();
    rtc_set_datetime(0, 0, 0, 0, hour, min);
}*/
char display_first_bcd (byte n )
{
    return n/10+'0' ;
}
char display_second_bcd (byte n )
{
    return n%10+'0';
}

void displayNumber(int n)
{
    output_d(LED_MAP[n/10]);
    //printf("Count is %d", n/10);
    output_low(display1);
    delay_us(2000);
    output_high(display1);

    output_d(LED_MAP[n%10]);
    //printf("%d\r\n", n%10);
    output_low(display2);
    delay_us(2000);
    output_high(display2);
}

int const LCD_INIT_STRING[5] =
{
    0x38, // Func set: 8-bit, 2 lines
    0x08, // don't shift display, hide cursor
    1, // Clear display
    6, // Increment cursor
    0xc, // Display on
};

void sendLCD(int address, int n)
{
    output_low (LCD_E);
    delay_us (60);

    if(address)
        output_high (LCD_RS);
    else
        output_low (LCD_RS);

    delay_cycles(1);
    output_d (n);
    output_high (LCD_E);
    delay_ms (1);
    output_low (LCD_E);
    delay_ms(5);
}

void setupLCD(void)
{
    int i;

    output_low(LCD_RS);
    output_low(LCD_E);
    delay_ms(15);

    for(i=0 ;i < 3; i++)
    {
        output_d (0x30);
        delay_ms(5);
    }

    for(i=0; i < sizeof(LCD_INIT_STRING); i++)
    {
        sendLCD(0, LCD_INIT_STRING[i]);
    } 
}

void putcharLCD(char c)
{
    switch(c)
    {
        case '\r':
            sendLCD(0,1);
            delay_ms(2);
            break;
        case '\f':
            sendLCD(0, 0x80 );
            break;
        case '\n':
            sendLCD(0, 0xc0 );
            break;
        default:
            sendLCD(1,c);
            break;
    } 
}

void binaryLEDs (int n)
{
  //clearLEDs();
  int i;
  for (i = 0; i < 6; i++)
  {
    nextLEDs[i] = 0;
  }

  if(bit_test(n, 0))
  {
    singleLED(0, 1);
  }
  if(bit_test(n, 1))
  {
    singleLED(1, 1);
  }
  if(bit_test(n, 2))
  {
    singleLED(2, 1);
  }
}

void debounce(void)
{
  while(input(push));
  delay_ms(100); // Why?
  while(!input(push));
}

void delaySeconds (unsigned int seconds)
{
  printf("Delaying for %d seconds\n\r", seconds);
  delay_ms(seconds * 1000);
}

void cycleHold(void)
{
  while(!input(push))
  {
    printf("Holding...");
  }
}

void onePress(void)
{
  while(input(push));
  while(!input(push));
}

void singleLED(int LED, int1 set)
{
  nextLEDs[LED] = set;
  //setLED(LED, nextLEDs[set]);
  refresh();
}

void flipLED(int LED)
{
  int i;
  for (i = 0; i < 6; i++)
  {
    nextLEDs[i] = 0;
  }
  //nextLEDs[6] = {0, 0, 0, 0, 0, 0};
  nextLEDs[LED] = 1;
  refresh();
}

void refresh(void)
{
  int i;
  for (i = 0; i < 6; i++)
  {
    //if(nextLEDs[i] == currentLEDs[i])
    //if(currentLEDs[i] == nextLEDs[i])
    //{
      currentLEDs[i] = nextLEDs[i];
      setLED(i, currentLEDs[i]);
      //setLED(i, nextLEDs[i]);
    //}
  }
}
//void clearArray
void setLED(int select, int1 setBit)
{
  if(setBit == 1)
  {
    switch (select)
    {
      case 0:
        output_low(greenLED);
        break;
      case 1:
        output_low(yellowLED);
        break;
      case 2:
        output_low(redLED);
        break;
      case 3:
        output_low(greenLEDext);
        break;
      case 4:
        output_low(yellowLEDext);
        break;
      case 5:
        output_low(redLEDext);
        break;
    }
  }
  else
  {
    switch (select)
    {
      case 0:
        output_high(greenLED);
        break;
      case 1:
        output_high(yellowLED);
        break;
      case 2:
        output_high(redLED);
        break;
      case 3:
        output_high(greenLEDext);
        break;
      case 4:
        output_high(yellowLEDext);
        break;
      case 5:
        output_high(redLEDext);
        break;
    }
  }
}
void clearLEDs(void)
{
  //int1 currentLEDs[6] = {0, 0, 0, 0, 0, 0};
  // nextLEDs[6] = {0, 0, 0, 0, 0, 0};
  output_high(greenLED);
  output_high(yellowLED);
  output_high(redLED);
  printf("All LEDs cleared\n\r");
}