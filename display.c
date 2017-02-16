#include <avr/io.h>
#include "logo.h"
#include <util/delay.h>
#include "arial_bold_14.h"

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
    LCD_puts("27'C");
    gui_lpg(73);
    gui_coolant_water(50);
    gui_battery_voltage(40);
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
        LCD_drawBMP(light,0,0,20,20);
    else
        LCD_clearRect(0,0,20,20);
}

void gui_door_open(unsigned char value)
{
    if (value)
        LCD_drawBMP(door,20,0,20,20);
    else
        LCD_clearRect(20,0,40,20);
}

void gui_alternator(unsigned char value)
{
    if (value)
        LCD_drawBMP(battery,40,0,20,20);
    else
        LCD_clearRect(40,0,60,20);
}

void gui_handbrake(unsigned char value)
{
    if (value)
        LCD_drawBMP(park,60,0,20,20);
    else
        LCD_clearRect(60,0,80,20);
}

void gui_lpg(unsigned char value)
{
    unsigned char i=0;

    value = 0.3 * value;

    for (i=0;i<value;i++)
    {
        if (i%2 == 0)
            LCD_drawLine(0,53-i,12,53-i);
    }

    LCD_setCursorXY(0,63);
    LCD_puts("73%");
}

void gui_coolant_water(unsigned char value)
{
    unsigned char i=0;

    value = 0.3 * value;

    for (i=0;i<value;i++)
    {
        if (i%2 == 0)
            LCD_drawLine(115,53-i,127,53-i);
    }

    LCD_setCursorXY(105,63);
    LCD_puts("90'C");
}

void gui_battery_voltage(unsigned char value)
{
    LCD_setCursorXY(50,63);
    LCD_puts("12.4V");
}
