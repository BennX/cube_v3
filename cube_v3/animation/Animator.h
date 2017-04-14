#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__
#include "../util/LinkedList.h"
#include "Animation.h"

class Animator
{
//variables
private:
	LinkedList<Animation *> m_animations;
	Animation* m_current;
	
//functions
public:
	Animator();
	~Animator();
	void update(const uint16_t& delta);
	
private:
	Animator( const Animator &c );
	Animator& operator=( const Animator &c );

}; //Animator

#endif //__ANIMATOR_H__
