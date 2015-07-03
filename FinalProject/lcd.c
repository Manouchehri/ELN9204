/*This entire library was taken from Stephen Ryan's example code, with some slight changes*/

int const LCD_INIT_STRING[5] =
{
    0x38, // Func set: 8-bit, 2 lines
    0x08, // don't shift display, hide cursor
    1, // Clear display
    6, // Increment cursor
    0xc, // Display on
};

int LCD_E; /*This is to allow switching LCD screens instead of forcing one at compile time*/

void sendLCD(int address, int n)
{
    output_low (LCD_E);
    delay_us (60); /*Might be a little long?*/

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
            sendLCD(0, 1);
            delay_ms(2);
            break;
        case '\f': /*I had problems with /c, so that's why I changed it to /f*/
            sendLCD(0, 0x80);
            break;
        case '\n':
            sendLCD(0, 0xc0);
            break;
        default:
            sendLCD(1, c);
            break;
    }
}
