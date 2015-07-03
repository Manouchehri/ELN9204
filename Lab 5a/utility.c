void delaySeconds (unsigned int delayMs);
void setLED(int);
void clearLEDs (void);
void onePress(void);
void cycleHold(void);
void binaryLEDs (int n);
void debounce(void);

void binaryLEDs (int n)
{
  clearLEDs();

  if(bit_test(n, 0))
  {
    setLED(0);
  }
  if(bit_test(n, 1))
  {
    setLED(1);
  }
  if(bit_test(n, 2))
  {
    setLED(2);
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

void setLED(int select)
{
  switch (select)
  {
    case 0:
    {
      output_low(greenLED);
      printf("Green LED on\n\r");
      break;
    }
    case 1:
    {
      output_low(yellowLED);
      printf("Yellow LED on\n\r");
      break;
    }
    case 2:    
    {
      output_low(redLED);
      printf("Red LED on\n\r");
      break;
    }
  }
}

void clearLEDs(void)
{
  output_high(greenLED);
  output_high(yellowLED);
  output_high(redLED);
  printf("All LEDs cleared\n\r");
}
