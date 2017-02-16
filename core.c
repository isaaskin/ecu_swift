#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DDRREADPORT1 DDRA
#define READPORT1    PINA

#define DDRREADPORT2 DDRB
#define READPORT2    PINB

#define PARKLIGHT   1<<0
#define FRONTLEFT   1<<1
#define FRONTRIGHT  1<<2
#define BACKLEFT    1<<3
#define BACKRIGHT   1<<4
#define BAGGAGE     1<<5
#define ALTERNATOR  1<<6
#define OIL         1<<7
#define HANDBRAKE   1<<0
#define FAN         1<<1
#define IGNITION    1<<2

#define TIMEMARKER1 1<<3

// declares values
unsigned char val_parklight = 0;
unsigned char val_parklight_last = 1;
unsigned char val_frontleft = 0;
unsigned char val_frontleft_last = 1;
unsigned char val_frontright = 0;
unsigned char val_frontright_last = 1;
unsigned char val_backleft = 0;
unsigned char val_backleft_last = 1;
unsigned char val_backright = 0;
unsigned char val_backright_last = 1;
unsigned char val_baggage = 0;
unsigned char val_baggage_last = 1;
unsigned char val_alternator = 0;
unsigned char val_alternator_last = 1;
unsigned char val_oil = 0;
unsigned char val_oil_last = 1;
unsigned char val_handbrake = 0;
unsigned char val_handbrake_last = 0;
unsigned char val_fan = 0;
unsigned char val_fan_last = 1;
unsigned char val_ignition = 0;
unsigned char val_ignition_last = 1;

// declare flags
unsigned char flag_parklight_update = 0;
unsigned char flag_frontleft_update = 0;
unsigned char flag_frontright_update = 0;
unsigned char flag_backleft_update = 0;
unsigned char flag_backright_update = 0;
unsigned char flag_baggage_update = 0;
unsigned char flag_alternator_update = 0;
unsigned char flag_oil_update = 0;
unsigned char flag_handbrake_update = 0;
unsigned char flag_fan_update = 0;
unsigned char flag_ignition_update = 0;

void ports_init(void);
void interrupts_init(void);
void read_values(void);
void read_last_values(void);
void check_parklight(void);
void check_doors(void);
void check_doors_indicator(void);
void check_alternator(void);
void check_handbrake(void);

ISR(TIMER1_COMPA_vect)
{
    PORTB |= TIMEMARKER1;
    read_values();
    check_parklight();
    check_doors();
    check_alternator();
    check_handbrake();

    //_delay_ms(50);
    read_last_values();
    PORTB &= ~TIMEMARKER1;
}

ISR(TIMER3_COMPA_vect)
{
    // codes
    _delay_ms(1);
}

ISR(INT5_vect)
{
    gui_handbrake(1);
}

void ports_init(void)
{
    DDRREADPORT1 = 0x00;
    DDRREADPORT1 &= ~(HANDBRAKE | FAN | IGNITION);
    DDRB |= (TIMEMARKER1) | _BV(PORTB4);
}

void interrupts_init(void)
{
    // Prescaler is set to 256 for Timer/Counter-1
    TCCR1B |= (1 << CS12) | (1 << WGM12);
    // 16us*6250 = 100ms for Timer/Counter-1
    OCR1A = 6250;
    // 16us*3125 = 50ms for Timer/Counter-1
    TIMSK |= _BV(OCIE1A);

    // Prescaler is set to 256 for Timer/Counter-3
    TCCR3B |= (1 << CS32) | (1 << WGM32);
    // 16us*625 = 10ms for Timer/Counter-3
    OCR3A = 625;
    // 16us*3125 = 50ms for Timer/Counter-3
    //ETIMSK |= _BV(OCIE3A);

    // External interrupt for INT5
    EICRB |= (1<<ISC51) | (1<<ISC50);
    // Enable
    EIMSK |= (1<<INT5);
    sei();
}


void read_values(void)
{
    val_parklight = READPORT1 & PARKLIGHT;
    val_frontleft = READPORT1 & FRONTLEFT;
    val_frontright = READPORT1 & FRONTRIGHT;
    val_backleft = READPORT1 & BACKLEFT;
    val_backright = READPORT1 & BACKRIGHT;
    val_baggage = READPORT1 & BAGGAGE;
    val_alternator = READPORT1 & ALTERNATOR;
    val_oil = READPORT1 & OIL;
    val_handbrake = READPORT2 & HANDBRAKE;
    val_fan = READPORT2 & FAN;
    val_ignition = READPORT2 & IGNITION;
}

void read_last_values(void)
{
    val_parklight_last = val_parklight;
    val_frontleft_last = val_frontleft;
    val_frontright_last = val_frontright;
    val_backleft_last = val_backleft;
    val_backright_last = val_backright;
    val_baggage_last = val_baggage;
    val_alternator_last = val_alternator;
    val_oil_last = val_oil;
    val_handbrake_last = val_handbrake;
    val_fan_last = val_fan;
    val_ignition_last = val_ignition;
}

void check_parklight(void)
{
    if (val_parklight != val_parklight_last)
    {
        if (val_parklight == PARKLIGHT)
            gui_parklight(1);
        else
            gui_parklight(0);
    }
}

void check_doors(void)
{
    if (val_frontleft != val_frontleft_last)
    {
        if (val_frontleft == FRONTLEFT)
            check_doors_indicator();
        else
            check_doors_indicator();
    }

    if (val_frontright != val_frontright_last)
    {
        if (val_frontright == FRONTRIGHT)
            check_doors_indicator();
        else
            check_doors_indicator();
    }

    if (val_backleft != val_backleft_last)
    {
        if (val_backleft == BACKLEFT)
            check_doors_indicator();
        else
            check_doors_indicator();
    }

    if (val_backright != val_backright_last)
    {
        if (val_backright == BACKRIGHT)
            check_doors_indicator();
        else
            check_doors_indicator();
    }

    if (val_baggage != val_baggage_last)
    {
        if (val_baggage == BAGGAGE)
            gui_door_open(1);
        else
            gui_door_open(0);
    }
}

void check_doors_indicator(void)
{
    if (val_frontleft | val_frontright | val_backleft | val_backright | val_baggage)
        gui_door_open(1);
    else
        gui_door_open(0);
}

void check_alternator(void)
{
    if (val_alternator != val_alternator_last)
    {
        if (val_alternator == ALTERNATOR)
            gui_alternator(0);
        else
            gui_alternator(1);
    }
}

void check_handbrake(void)
{
    if (val_handbrake != val_handbrake_last)
    {
        if (val_handbrake == HANDBRAKE)
            gui_handbrake(1);
        else
            gui_handbrake(0);
    }
}
