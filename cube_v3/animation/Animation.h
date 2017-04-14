#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include <avr/pgmspace.h>
class Animation
{
public:
    virtual PGM_P name() = 0;
    virtual void update(const uint16_t& delta) = 0;
};

#endif