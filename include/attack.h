#ifndef INCLUDED_ATTACK_H
#define INCLUDED_ATTACK_H

#include <action.h>
#include <iostream>

class Target
{
public:
	virtual ~Target () {}
	virtual void attack (unsigned int damage) = 0;
	virtual unsigned int damage () const = 0;
};

class Attack : public Action
{
	public:
		Attack (Target* target, Target* attacker) :
			_target (target)
		      , _attacker (attacker)
		{
		}

		bool operator== (const Attack& a) const
		{
			return (_target == a._target) && (_attacker == a._attacker); 
		}	

		bool operator!= (const Attack& a) const
		{
			return !(*this == a); 
		}

		void apply ();

		friend std::ostream& operator<< (std::ostream& s, const Attack& a);
	public:
		Target* _target;
		Target* _attacker;
};

inline std::ostream& operator<< (std::ostream& s, const Attack& a)
{
	s << a._attacker->damage ();
	return s; 
}

inline void Attack::apply ()
{
	unsigned int retaliation = _target->damage ();
	_target->attack (_attacker->damage ());
	_attacker->attack (retaliation);
}

#endif
