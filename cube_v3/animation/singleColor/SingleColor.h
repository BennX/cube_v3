#ifndef __SINGLECOLOR_H__
#define __SINGLECOLOR_H__

#include "../Animation.h"

class SingleColor: public Animation
{
//variables
public:
protected:
private:

//functions
public:
    SingleColor();
    ~SingleColor();

    void update(const uint16_t& delta);
    PGM_P name();
protected:
private:
    SingleColor(const SingleColor& c);
    SingleColor& operator=(const SingleColor& c);

}; //SingleColor

#endif //__SINGLECOLOR_H__
