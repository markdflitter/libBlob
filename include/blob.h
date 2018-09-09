#ifndef INCLUDED_BLOB_H
#define INCLUDED_BLOB_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <pt.h>
#include <action.h>
#include <movement.h>
#include <attack.h>
#include <rnd.h>

class Blob : public Moveable, public Attackable
{
public:
	Blob (const std::string& name = ""
	      , std::function<double (double)> rnd = [](double) {return 0.0;}
	      , double x = 0.0
	      , double y = 0.0
              , double speed = 0.0
	      , double runningSpeed = 0.0
              , double smell = 0.0
              , unsigned int strength = 0
	      , unsigned int endurance = 0
	      , double aggression = 1.0) :
		  _name (name)
		, _rnd (rnd)
		, _speed (speed)
		, _runningSpeed (runningSpeed)
		, _smell (smell)
		, _strength (strength)
		, _endurance (endurance)
		, _aggression (aggression)
		, _state ("newborn")
 		, _fatigue (0)
		, _dead (false)
		, _tired (false)
			{
				_points.push_back (Pt<double> (x,y));
			}

	std::string name () const {return _name;}
	double x () const {return _points.back ().x ();}
	double y () const {return _points.back ().y ();}
	double speed () const {return _speed;}
	double runningSpeed () const {return _runningSpeed;}
	double smell () const {return _smell;}
	unsigned int strength () const {return _strength;}
	unsigned int endurance () const {return _endurance;}
	double aggression () const {return _aggression;}

	std::string state () const {return _state;}

	double fatigue () const {return _fatigue;}
	bool isTired () const {return _tired;} 

	bool isDead () const {return _dead;}

	friend std::ostream& operator<<(std::ostream& s, const Blob& b);

	std::vector<Pt<double>> history () const {return _points;}
	
	double distance (const Blob& other) const
	{
		double dx = other.x () - x();
		double dy = other.y () - y();
		double d = sqrt ((dx * dx) + (dy * dy));

		return d; 
	}

	bool isInRange (const Blob& other, double range) const
	{
		return distance (other) <= range;
	}

	bool isInSameSquare (const Blob& other) const
	{
		return isInRange (other, sqrt (2));
	}
	
	bool canSmell (const Blob& other) const
	{
		return isInRange (other, _smell);
	}

	double angle (const Blob& other) const
	{
		double dx = x () - other.x ();
		double dy = y () - other.y ();

		return atan2 (dy, -dx) + M_PI/2;
	}

        void kill ()
	{
		_dead = true;
		_state = "dead";
	}

	void attack (unsigned int damage)
	{
		if (_strength >= damage)
		{
			_strength -= damage;
		}
		else
		{
			_strength = 0;
		}

		if (_strength == 0)
		{
			kill ();
		}
	}

        void move (double speed, double angleInRadians, const std::string& newState) 
	{
		_previousAngleInRadians = angleInRadians;

		double denormalisedMoveDirection = _previousAngleInRadians - M_PI / 2;
		double newX = x () + speed * cos (denormalisedMoveDirection);
		double newY = y () - speed * sin (denormalisedMoveDirection);
			
		_points.push_back (Pt<double> (newX, newY));
		while (_points.size () > 500)
			_points.erase (_points.begin (), _points.begin () + 1);
	
		_state = newState;

		if (speed > _speed)
		{
			if (_fatigue < _endurance) _fatigue++;
		}
		else
		{
			if (_fatigue > 0) _fatigue--;
		}
		if (_fatigue == 0) _tired = false;
		if (_fatigue == _endurance) _tired = true; 
	}
        
	std::shared_ptr <Action> createActionDead ()
        {
		return std::shared_ptr<Action> (new Movement (this, "dead", 0, 0));
	}
 
        std::shared_ptr <Action> createActionWander ()
        {
		double angle = _rnd (_previousAngleInRadians);
		return std::shared_ptr<Action> (new Movement (this, "wandering", _speed, angle));
	}
        
	std::shared_ptr <Action> createActionHunt (const Blob& target)
        {
		return std::shared_ptr <Action> (new Movement (this,
			 "hunting " + target.name () + (!isTired () ? " (fast)" : ""),
			std::min (isTired() ? _speed : _runningSpeed, distance (target)),
			angle (target)));
	}
        
	std::shared_ptr <Action> createActionFlee (const Blob& target)
        {
		return std::shared_ptr <Action> (new Movement (this,
				 "running from " + target.name () + (!isTired () ? " (fast)" : ""),
				isTired () ? _speed : _runningSpeed,
				_rnd ((0.9 * _previousAngleInRadians + 0.1 * (angle (target) + M_PI)))));
	}
         
	std::shared_ptr <Action> createActionAttack (Blob& target)
        {
		return std::shared_ptr <Action> (new Attack (&target, _strength));
	}

	std::shared_ptr <Action> chooseNextAction (std::vector<Blob>& others)
	{
		if (isDead())
		{
			return createActionDead ();
		}
		
		struct Pair 
		{
			double _weight;
			Blob* _blob;
		};

		std::vector <Pair> attackTargets;
		std::vector <Pair> huntTargets;
		for (auto& b : others)
		{
			if ((&b != this) && !b.isDead ())
			{
				if (isInSameSquare (b) && (b.strength () < _strength))
				{
					double weight = -b.strength ();
					attackTargets.push_back (Pair {weight, &b});
				}
				else if (canSmell (b))
				{
					double aggression_multiplier = _aggression;
					if (b._strength > _strength)
						aggression_multiplier = 1.0 - aggression_multiplier;
					double weight = (1.0 - (distance (b) / _smell)) * aggression_multiplier;
					huntTargets.push_back (Pair {weight, &b});
				}
			}
		}

		std::sort (attackTargets.begin (), attackTargets.end (),
			   [] (const Pair& lhs,
			       const Pair& rhs) {return lhs._weight < rhs._weight;});
		std::sort (huntTargets.begin (), huntTargets.end (),
			   [] (const Pair&  lhs,
			       const Pair& rhs) {return lhs._weight < rhs._weight;});
		
		if (attackTargets.size () > 0)
		{
			return createActionAttack (*(attackTargets.back ())._blob);
		}

		for (auto it = huntTargets.rbegin (); it != huntTargets.rend (); it++)
		{
			if (it->_weight > 0)
			{
				if (it->_blob->_strength > _strength)
					return createActionFlee (*(it->_blob));
				else
 					return createActionHunt (*(it->_blob));
			}
		}

		return createActionWander ();
	}
private:
	std::function<double(double)> _rnd;
	std::vector<Pt<double>> _points;

	std::string _name;
	std::string _state;
	double _speed;
        double _runningSpeed;
	double _smell;
	unsigned int _strength;
	unsigned int _endurance;
	double _aggression;

	unsigned int _fatigue;
	bool _tired;

	bool _dead;
	double _previousAngleInRadians = 0;
};

inline std::ostream& operator<< (std::ostream& s, const Blob& b)
{
	s << b.x () << "," << b.y ();
	return s; 
}

#endif

