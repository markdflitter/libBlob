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
#include <fight.h>
#include <rnd.h>

class Blob : public Moveable, public Target
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
	      , double aggression = 0.5
	      , unsigned int longevity = 100
	      , std::function<double (double)> aggression_rnd = [](double aggression) {return aggression;}) :
		  _name (name)
		, _rnd (rnd)
		, _speed (speed)
		, _runningSpeed (runningSpeed)
		, _smell (smell)
		, _initialStrength (strength)
		, _strength (strength)
		, _endurance (endurance)
		, _aggression (aggression)
		, _longevity (longevity)
		, _aggression_rnd (aggression_rnd)
		, _state ("newborn")
 		, _fatigue (0)
		, _tired (false)
		, _age (0)
		, _dead (false)
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
	unsigned int initialStrength () const {return _initialStrength;}
	unsigned int damage () const {return _strength;}
	unsigned int endurance () const {return _endurance;}
	double aggression () const {return _aggression;}
 	unsigned int longevity () const {return _longevity;}
	unsigned int age () const {return _age;}
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

	void growOlder ()
	{
		if (!isDead ())
		{
			_age++;

			if (_age >= longevity ())
			{
				kill ();
			}
		}
	}

	void takeDamage (unsigned int damage)
	{
		growOlder ();
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
		growOlder ();

		_previousAngleInRadians = angleInRadians;

		double denormalisedMoveDirection = _previousAngleInRadians - M_PI / 2;
		double newX = x () + speed * cos (denormalisedMoveDirection);
		double newY = y () - speed * sin (denormalisedMoveDirection);
	
		newX = std::max (-WORLD_SIZE.x (), std::min (WORLD_SIZE.x (), newX));
		newY = std::max (-WORLD_SIZE.y (), std::min (WORLD_SIZE.y (), newY));
		
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
			if (_strength < _initialStrength) _strength++;
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
        
	std::shared_ptr <Action> createActionFlee (const Blob& target)
        {
		return std::shared_ptr <Action> (new Movement (this,
				 "running from " + target.name () + (!isTired () ? " (fast)" : ""),
				isTired () ? _speed : _runningSpeed,
				_rnd ((0.9 * _previousAngleInRadians + 0.1 * (angle (target) + M_PI)))));
	}
       
	std::shared_ptr <Action> createActionHunt (const Blob& target)
        {
		return std::shared_ptr <Action> (new Movement (this,
			 "hunting " + target.name () + (!isTired () ? " (fast)" : ""),
			std::min (isTired() ? _speed : _runningSpeed, distance (target)),
			angle (target)));
	}  
	
	std::shared_ptr <Action> createActionFight (Blob& target)
        {
		return std::shared_ptr <Action> (new Fight (&target, this));
	}

	std::shared_ptr <Action> createActionAttack (Blob& target)
        {
		if (isInSameSquare (target))
		{
			std::cout << "in same sq" << std::endl;
			return createActionFight (target);
		}
		else
		{
			std::cout << "not in same sq" << std::endl;
			return createActionHunt (target);
		}
	}

	double relativeDifference (double v1, double v2)
	{
		assert (v1 >= 0.0);
		assert (v2 >= 0.0);
		return (v1 - v2) / (v1 + v2) / 2; 
	}

	double inflictDamageWeightForAttacking (const Blob& b)
	{
		return relativeDifference (damage (), b.strength ()) * 2.0;
	}

	double avoidDamageWeightForAttacking (const Blob& b)
	{
		return relativeDifference (strength (), b.damage ()) * 2.0;
	}

	double avoidDamageWeightForFleeing (const Blob& b)
	{
		return relativeDifference (b.damage (), strength ()) * 2.0;
	}

	double distanceWeight (const Blob& b)
	{
		if (isInSameSquare (b))
		{
			return 1.0;
		}
		else if (canSmell (b)) 
		{
			return 1.0 - (distance (b) / _smell);
		}
		else
		{
			return 0.0;
		}
	}

	double attackWeight (const Blob& b)
	{
		return distanceWeight (b) * std::max (inflictDamageWeightForAttacking (b), avoidDamageWeightForAttacking (b));
	}	
	
	double fleeWeight (const Blob& b)
	{
		return distanceWeight (b) * avoidDamageWeightForFleeing (b);
	}
	
	struct ActionPossibility 
	{
		enum {attack, flee} action;
		double weight;
		Blob* target;
	};

	std::vector<ActionPossibility> findPossibleActions (std::vector<Blob>& others)
	{	
		std::vector <ActionPossibility> possibilities;

		for (auto& b : others)
		{
			if ((&b != this) && !b.isDead ())
			{
				double a = _aggression_rnd (_aggression);

				if (isInSameSquare (b) || canSmell (b))
				{
					possibilities.push_back (
						ActionPossibility {ActionPossibility::attack, attackWeight (b) + a, &b});
					possibilities.push_back (
						ActionPossibility {ActionPossibility::flee, fleeWeight (b) - a, &b});
				}
			}
		}
		
		return possibilities;
	}

	std::shared_ptr<Action> selectAction (std::vector <ActionPossibility> possibilities)
	{
		if (possibilities.size () > 0)
		{
			std::sort (possibilities.begin (), possibilities.end (),
			   [] (const ActionPossibility& lhs,
			       const ActionPossibility& rhs) {
			return lhs.weight < rhs.weight;});
	
			ActionPossibility selected_option = (possibilities.back ());
			switch (selected_option.action)
			{
				case ActionPossibility::attack:
 					return createActionAttack (*(selected_option.target));
				case ActionPossibility::flee:
					return createActionFlee (*(selected_option.target));
			}
		}
		return createActionWander ();
	}

	std::shared_ptr <Action> chooseNextAction (std::vector<Blob>& blobs)
	{
		if (isDead())
		{
			return createActionDead ();
		}
		else
		{
			return selectAction (findPossibleActions (blobs));
		}
	}
private:
	Pt<double> WORLD_SIZE = Pt<double>(2000.0, 1000.0);

	std::function<double(double)> _rnd;
	std::vector<Pt<double>> _points;

	std::string _name;
	std::string _state;
	double _speed;
        double _runningSpeed;
	double _smell;
	unsigned int _initialStrength;
	unsigned int _strength;
	unsigned int _endurance;
	double _aggression;
	unsigned int _longevity;
	std::function<double(double)> _aggression_rnd;
	unsigned int _fatigue;
	bool _tired;

	unsigned int _age;
	
	bool _dead;
	double _previousAngleInRadians = 0;
};

inline std::ostream& operator<< (std::ostream& s, const Blob& b)
{
	s << b.x () << "," << b.y ();
	return s; 
}

#endif

