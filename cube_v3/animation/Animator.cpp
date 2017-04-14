#include "Animator.h"
#include "singleColor/SingleColor.h"

// default constructor
Animator::Animator()
{
	//init all animations
	m_animations.add(new SingleColor());
	m_current = m_animations.get(0);
} //Animator

// default destructor
Animator::~Animator()
{
} //~Animator

void Animator::update(const uint16_t& delta) 
{
	m_current->update(delta);
}