#define F_CPU 22118400
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdlib.h>
void* operator new(size_t size);
void operator delete(void* ptr);
void* operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void* ptr)
{
    free(ptr);
}

#include "display/Display.h"
#include "cube/Cube.h"
#include "input/Input.h"
#include "animation/Animator.h"

void initCubeRoutine();
void ledToggle();
long long ms();
void colors();

int main(void)
{
    cli();
    Display::init();

    Display::out_p(0, 0) << PSTR("Initialization");
    //init the cube
    Input& input = Input::getInstance();
    Animator l_animator;
    initCubeRoutine();
    _delay_ms(1);
    sei();
    Display::clear();

    //here it starts running
    colors(); //show 125 different colors till user input

    long long start = 1; //
    uint16_t delta = 0; // delta value always positive
    /* Replace with your application code */
    while(true)
    {
        start = ms();
        Display::update(delta);
        l_animator.update(delta);
        delta = ms() - start;
    }
}

/**
 * used to check if still a life
 */
void ledToggle()
{
    PORTB ^= (1 << PB3); //toggle the test led
}

void initCubeRoutine()
{
    //16 Bit timer!
    TCCR1A = 0x00; // CTC on OCR1A
    TCCR1B |= (1 << CS00) | (1 << WGM12); //no pre scaler
    TIMSK1 |= (1 << OCIE1A); //compare interrupt on A
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
    {
        for(uint8_t y = 0; y < 5; y++)
        {
            for(uint8_t x = 0; x < 5; x++)
            {
                cub(x, y, z) = RGB(x / 4.0 * MAX_COLOR, y / 4.0 * MAX_COLOR, z / 4.0 * MAX_COLOR);
            }
        }
    }

    Display::clear();
    Display::out_p(0, 0) << PSTR("Show");
    Display::out_p(1, 0) << PSTR("Colors");
    Display::out_p(2, 0) << PSTR("Click 4 continue");
    while(!Input::getInstance().clicked())
        ;//nop for the first click ;)
}