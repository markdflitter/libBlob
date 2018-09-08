#ifndef INCLUDED_ATTACK_H
#define INCLUDED_ATTACK_H

#include <action.h>
#include <iostream>

class Attackable
{
public:
	virtual ~Attackable () {}
	virtual void attack (double strength) = 0;
};

class Attack : public Action
{
	public:
		Attack (Attackable* target, double strength) :
			_target (target)
			, _strength (strength)
		{
		}

		bool operator== (const Attack& a) const
		{
			return (_target == a._target) 
			    && (_strength == a._strength);
		}	

		bool operator!= (const Attack& a) const
		{
			return !(*this == a); 
		}

		void apply ();

		friend std::ostream& operator<< (std::ostream& s, const Attack& a);
	public:
		Attackable* _target;
		double _strength;
};

inline std::ostream& operator<< (std::ostream& s, const Attack& a)
{
	s << a._strength;
	return s; 
}

inline void Attack::apply ()
{
	_target->attack (_strength);
}

#endif
