#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    ports_init();
    gui_init();
    interrupts_init();
    //gui_test();

    while(1)
    {
    };

    return 0;
}
