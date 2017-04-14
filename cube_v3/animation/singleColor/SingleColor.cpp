#include "SingleColor.h"
#include "../../cube/Cube.h"
// default constructor
SingleColor::SingleColor()
{
} //SingleColor

// default destructor
SingleColor::~SingleColor()
{
} //~SingleColor

PGM_P SingleColor::name()
{
    return PSTR("Single Color");
}

void SingleColor::update(const uint16_t& delta)
{
    Cube& cube = Cube::getInstance();
    for(uint8_t x = 0; x < 5; x++)
    {
        for(uint8_t y = 0; y < 5; y++)
        {
            for(uint8_t z = 0; z < 5; z++)
            {
                cube(x,y,z) = RGB(15,15,15);
            }
        }
    }
}