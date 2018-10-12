#ifndef INCLUDED_FIGHT_H
#define INCLUDED_FIGHT_H

#include <action.h>
#include <iostream>

class Target
{
public:
	virtual ~Target () {}
	virtual void takeDamage (unsigned int damage) = 0;
	virtual void inflictDamage (Target* target) = 0;
	virtual void retaliate (Target* target) = 0;
};

class Fight : public Action
{
	public:
		Fight (Target* target, Target* attacker) :
			_target (target)
		      , _attacker (attacker)
		{
		}

		bool operator== (const Fight& a) const
		{
			return (_target == a._target) && (_attacker == a._attacker); 
		}	

		bool operator!= (const Fight& a) const
		{
			return !(*this == a); 
		}

		void apply ();
	public:
		Target* _target;
		Target* _attacker;
};

inline void Fight::apply ()
{
	_attacker->inflictDamage (_target);
	_target->retaliate (_attacker);
}

#endif
