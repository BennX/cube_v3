#define F_CPU 22118400
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "display/Display.h"
#include "cube/Cube.h"
#include "input/Input.h"

void initCubeRoutine();
void ledToggle();
long long ms();
void colors();

int main(void)
{
    /* Replace with your application code */
    while(true)
    {
    }
}


/**
 * used to check if still alife
 */
void ledToggle()
{
    PORTB ^= (1 << PB3); //toggle the testled
}

void initCubeRoutine()
{
    //16 Bit timer!
    TCCR1A = 0x00; // CTC on OCR1A
    TCCR1B |= (1 << CS00) | (1 << WGM12); //kein prescaler
    TIMSK1 |= (1 << OCIE1A); //compare interupt on A
    //OCR1A = 0x0ACD;//2765  = 8khz
    //OCR1A = 2212; // 10khz
    OCR1A = 1843;// 12khz
    //OCR1A = 1580; // 14khz
    //OCR1A = 1382; // 16khz
}

long long millis = 0;
long long ms()
{
    return millis;
}

uint8_t counter = 0;
ISR(TIMER1_COMPA_vect)
{
    Cube::getInstance().render();

    counter++;
    if(counter % 12 == 0) //12khz
    {
        // 1khz routine here no need to clean counter
        millis++;
        Input::getInstance().update();
    }
}

void colors()
{
    Cube& cub = Cube::getInstance();
    for(uint8_t z = 0; z < 5; z++)
        for(uint8_t y = 0; y < 5; y++)
            for(uint8_t x = 0; x < 5; x++)
            {
                cub(x, y, z) = RGB(x / 4.0 * MAX_COLOR, y / 4.0 * MAX_COLOR, z / 4.0 * MAX_COLOR);
            }

    Display::clear();
    Display::out_p(0, 0) << PSTR("Show");
    Display::out_p(1, 0) << PSTR("Colors");
    Display::out_p(2, 0) << PSTR("Click 4 continue");
    while(!Input::getInstance().clicked())
        ;//nop for the first click ;)
}