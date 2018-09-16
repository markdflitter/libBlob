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
		return std::shared_ptr <Action> (new Attack (&target, this));
	}

	std::shared_ptr <Action> chooseNextAction (std::vector<Blob>& others)
	{
		if (age () >= longevity ())
		{
			kill ();
		}
		else if (!isDead ())
		{
			_age++;
		}

		if (isDead())
		{
			return createActionDead ();
		}
		
		struct Pair 
		{
			enum {attack, hunt, flee} _action;
			double _weight;
			double _aggression_multiplier;
			Blob* _blob;
		};

		std::vector <Pair> targets;
		for (auto& b : others)
		{
			if ((&b != this) && !b.isDead ())
			{
				double aggression_multiplier = _aggression_rnd (_aggression);
					
				// if two blobs are in the same square, consider attacking
				if (isInSameSquare (b))
				{
					//std::cout << "same sq" << '\n';
					// only consider attacking weaker blobs
					// weaker means my damage is more than their strength
					// OR their damage is less than my strength
					// (it doesn't mean their damage is less than mine, because that could still kill me
					// it also doesn't mean their strength is less than mine for the same reason)
					// ie ((damage () > b.strength ()) || (b.damage () < strength ()))
					// at the moment, this reduces to:
					// ((strength () > b.strength ()) || (b.strength () < strength ()))
					// which is clearly redundant, but when we separate strength and hit points, it won't b
 					if ((damage () > b.strength ()) || (b.damage () < strength ()))
					{
						//std::cout << "weaker" << '\n';
						// we want to favour attacking the weakest, so use calculate
						// the two differentials and take the biggest
						//std::cout << damage () << " " << b.strength () << '\n';
						//std::cout << b.damage () << " " << strength () << '\n';
						//std::cout << ((double) damage () - b.strength ()) / (damage () + b.strength ()) << '\n';
						//std::cout << ((double) strength () - b.damage ()) / (strength () + b.damage ()) << '\n';
						double weight = (std::max (
							((double) damage () - b.strength ()) / (damage () + b.strength ()),
							((double) strength () - b.damage ()) / (strength () + b.damage ())) + 1) / 2;
						//std::cout << weight << '\n';
						// we also use the aggression multipler, to randomise choice
						// whether to attack
						//std::cout << aggression_multiplier << '\n';
						if (aggression_multiplier >= 0.5)
						{
							//std::cout << "adding target" << '\n';
							targets.push_back (Pair {Pair::attack, weight, aggression_multiplier, &b});
						}
					}
				}
				// if another blob is in sense range, consider attacking or fleeing
				if (canSmell (b))
				{
					// we want to favour closer blobs, so calculate a distance percentage
					double distance_multiplier = 1.0 - (distance (b) / _smell);
					if (_smell == 0.0)
					{
						distance_multiplier = 0.0;
					}
					// we also want to favour weaker blobs (by the above definition)
					double damage_differential = (std::max (
						((double) damage () - b.strength ()) / (damage () + b.strength ()),
						((double) strength () - b.damage ()) / (strength () + b.damage ())) + 1) / 2;
					//std::cout << damage_differential << " " << distance_multiplier << '\n';
					//std::cout << "adding target2, weight =" << distance_multiplier * damage_differential << '\n';
					if (aggression_multiplier >= 0.5)
					{
						targets.push_back (Pair {Pair::hunt, distance_multiplier * damage_differential, aggression_multiplier, &b});
					}
					else
					{
						targets.push_back (Pair {Pair::flee, distance_multiplier * damage_differential, aggression_multiplier, &b});
					}
				}
			}
		}

		if (targets.size () > 0)
		{
			std::sort (targets.begin (), targets.end (),
			   [] (const Pair& lhs,
			       const Pair& rhs) {
			return lhs._weight  * lhs._aggression_multiplier < rhs._weight * rhs._aggression_multiplier;});
		
			// decide what to do
			// same Square => attack or flee, depending on aggression
			// else hunt or flee, depending on aggression
			Pair option = (targets.back ());
			switch (option._action)
			{
				case Pair::attack:
					return createActionAttack (*(option._blob));
				case Pair::hunt:
 					return createActionHunt (*(option._blob));
				case Pair::flee:
					return createActionFlee (*(option._blob));
			}
		}
		return createActionWander ();
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

