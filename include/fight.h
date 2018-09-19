#ifndef INCLUDED_FIGHT_H
#define INCLUDED_FIGHT_H

#include <action.h>
#include <iostream>

class Target
{
public:
	virtual ~Target () {}
	virtual void takeDamage (unsigned int damage) = 0;
	virtual unsigned int damage () const = 0;
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

		friend std::ostream& operator<< (std::ostream& s, const Fight& a);
	public:
		Target* _target;
		Target* _attacker;
};

inline std::ostream& operator<< (std::ostream& s, const Fight& a)
{
	s << a._attacker->damage ();
	return s; 
}

inline void Fight::apply ()
{
	unsigned int retaliation = _target->damage ();
	_target->takeDamage (_attacker->damage ());
	_attacker->takeDamage (retaliation);
}

#endif
