void delaySeconds (unsigned int delayMs);
void setLED(int select, int1 setBit);
void clearLEDs (void);
void onePress(void);
void cycleHold(void);
void binaryLEDs (int n);
void debounce(void);
void flip(int1 LED);
void refresh(void);

int1 currentLEDs[6] = {0, 0, 0, 0, 0, 0};
int1 nextLEDs[6] = {0, 0, 0, 0, 0, 0};

/*void binaryLEDs (int n)
{
  clearLEDs();

  if(bit_test(n, 0))
  {
    setLED(0, 1);
  }
  if(bit_test(n, 1))
  {
    setLED(1, 2);
  }
  if(bit_test(n, 2))
  {
    setLED(2, 3);
  }
}*/

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
  output_high(greenLED);
  output_high(yellowLED);
  output_high(redLED);
  printf("All LEDs cleared\n\r");
}
