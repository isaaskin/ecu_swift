#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    ports_init();
    gui_init();
    interrupts_init();


    while(1)
    {
        PORTB |= _BV(PORTB4);
        _delay_ms(50);
        PORTB &= ~_BV(PORTB4);
        _delay_ms(50);
    };

    return 0;
}
