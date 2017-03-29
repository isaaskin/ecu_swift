#include <avr/io.h>
#include "logo.h"
#include <util/delay.h>
#include "arial_bold_14.h"
#include <stdlib.h>

char text[10];
float a = 4.45;

char text_battery [8];

void gui_test(void)
{
    sprintf(text,"%.2f", a);
    LCD_setCursorXY(10,30);
    LCD_puts(text);
}

void gui_init(void)
{
    LCD_init();
    LCD_clr();
    LCD_drawFullBMP(logo);
    _delay_ms(1000);
    LCD_clr();
    LCD_drawLine(4,21,123,21);
    LCD_drawLine(4+12,53,123-12,53);
    LCD_setCursorXY(0,60);
    //LCD_puts("Left back door open");

    LCD_drawBMP(swift,40+10,26,40,26);
    //LCD_putgstr("27'C",Arial_Bold_14, 68+10,32);
    LCD_putgstr("5'C",Arial_Bold_14, 14+10,24);

    LCD_setCursorXY(68+10,32);
    //LCD_puts("27'C");
}

void gui_logo(void)
{
}

void gui_mainstream(void)
{
}

void gui_parklight(unsigned char value)
{
    if (value)
        LCD_drawBMP(light,4,0,20,20);
    else
        LCD_clearRect(4,0,24,20);
}

void gui_door_open(unsigned char value)
{
    if (value)
        LCD_drawBMP(door,24,0,20,20);
    else
        LCD_clearRect(24,0,44,20);
}

void gui_alternator(unsigned char value)
{
    if (value)
        LCD_drawBMP(battery,64,0,20,20);
    else
        LCD_clearRect(64,0,84,20);
}

void gui_handbrake(unsigned char value)
{
    if (value)
        LCD_drawBMP(park,44,0,20,20);
    else
        LCD_clearRect(44,0,64,20);
}

void gui_oil(unsigned char value)
{
   if (value)
        LCD_drawBMP(oil,84,0,20,20);
    else
        LCD_clearRect(84,0,104,20);
}

void gui_fan(unsigned char value)
{
   if (value)
        LCD_drawBMP(fan,104,0,20,20);
    else
        LCD_clearRect(104,0,124,20);
}

// 8 bit input value
// Battery voltage level
void gui_battery_voltage(unsigned char value)
{
    double val = ((double)value/255)*12;
    sprintf(text_battery, "%.2fV", val);
    LCD_clearRect(48,56,88,64);
    LCD_setCursorXY(48,63);
    LCD_puts(text_battery);
}

// 8 bit input value
// Coolant water temp value
void gui_cts(unsigned char value)
{
    unsigned char i=0;

    value = (value+1) / 16;

    LCD_clearRect(115,23,127,53);

    for (i=0;i<value;i++)
    {
        LCD_drawLine(115,53-i*2,126,53-i*2);
    }

    LCD_setCursorXY(105,63);
    LCD_puts("90'C");
}

// 8 bit input value
// LPG level
void gui_lpg_level(unsigned char value)
{
    unsigned char i=0;

    value = (value+1) / 16;

    LCD_clearRect(1,53,13,23);

    for (i=0;i<value;i++)
    {
        LCD_drawLine(1,53-i*2,12,53-i*2);
    }

    LCD_setCursorXY(0,63);
    LCD_puts("73%");
}




