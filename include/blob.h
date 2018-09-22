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
#include <assert.h>

class CreateBlob 
{
public:
	CreateBlob () :
	        _name ("")
	      , _position (make_pt (0.0, 0.0))
	      , _speed (0.0)
	      , _runningSpeed (0.0)
	      , _smell (0.0)
	      , _HP (0U)
	      , _endurance (0U)
	      , _aggression (0.0)
	      , _lifespan (0U)
	      , _damage (0U)
	      , _moveDirectionFn ([] (double) {return 0.0;})
	      , _aggressionFn ([](double a) {return a;})
		{
	      	}

	CreateBlob& name (const std::string& name) {_name = name; return *this;}
	CreateBlob& position (const Pt<double>& position) {_position = position; return *this;}
	CreateBlob& speed (double speed) {_speed = speed; return *this;}
	CreateBlob& runningSpeed (double runningSpeed) {_runningSpeed = runningSpeed; return *this;}
	CreateBlob& smell (double smell) {_smell = smell; return *this;}
	CreateBlob& HP (unsigned int HP) {_HP = HP; return *this;}
	CreateBlob& endurance (unsigned int endurance) {_endurance = endurance; return *this;}
	CreateBlob& aggression (double aggression) {_aggression = aggression; return *this;}
	CreateBlob& lifespan (unsigned int lifespan) {_lifespan = lifespan; return *this;}
	CreateBlob& damage (unsigned int damage) {_damage = damage; return *this;}
	CreateBlob& moveDirectionFn (std::function<double(double)> moveDirectionFn)
		{_moveDirectionFn = moveDirectionFn; return *this;}
	CreateBlob& aggressionFn (std::function<double(double)> aggressionFn)
		{_aggressionFn = aggressionFn; return *this;}
private:
	friend class Blob;
	
	std::string _name;
	Pt<double> _position;
	double _speed;
        double _runningSpeed;
	double _smell;
	unsigned int _HP;
	unsigned int _endurance;
	double _aggression;
	unsigned int _lifespan;
	unsigned int _damage;

	std::function<double(double)> _moveDirectionFn;
	std::function<double(double)> _aggressionFn;
};

class Blob : public Moveable, public Target
{
public:
	Blob (const CreateBlob& params) :
		  _name (params._name)
		, _speed (params._speed)
		, _runningSpeed (params._runningSpeed)
		, _smell (params._smell)
		, _maxHP (params._HP)
		, _HP (params._HP)
		, _endurance (params._endurance)
		, _aggression (params._aggression)
		, _lifespan (params._lifespan)
		, _damage (params._damage)
		, _moveDirectionFn (params._moveDirectionFn)
		, _aggressionFn (params._aggressionFn)
		,  _state ("newborn")
 		, _fatigue (0)
		, _tired (false)
		, _age (0)
		, _dead (false)
	{
		_points.push_back (params._position);
	}

	std::string name () const {return _name;}
	double x () const {return _points.back ().x ();}
	double y () const {return _points.back ().y ();}
	double speed () const {return _speed;}
	double runningSpeed () const {return _runningSpeed;}
	double smell () const {return _smell;}
	unsigned int HP () const {return _HP;}
	unsigned int maxHP () const {return _maxHP;}
	unsigned int damage () const {return _damage;}
	unsigned int endurance () const {return _endurance;}
	double aggression () const {return _aggression;}
 	unsigned int lifespan () const {return _lifespan;}
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

			if (_age >= lifespan ())
			{
				kill ();
			}
		}
	}

	void takeDamage (unsigned int damage)
	{
		growOlder ();
		if (_HP >= damage)
		{
			_HP -= damage;
		}
		else
		{
			_HP = 0;
		}

		if (_HP == 0)
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
			if (_HP < _maxHP) _HP++;
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
		double angle = _moveDirectionFn (_previousAngleInRadians);
		return std::shared_ptr<Action> (new Movement (this, "wandering", _speed, angle));
	}
        
	std::shared_ptr <Action> createActionFlee (const Blob& target)
        {
		return std::shared_ptr <Action> (new Movement (this,
				 "running from " + target.name () + (!isTired () ? " (fast)" : ""),
				isTired () ? _speed : _runningSpeed,
				_moveDirectionFn ((0.9 * _previousAngleInRadians + 0.1 * (angle (target) + M_PI)))));
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
			return createActionFight (target);
		}
		else
		{
			return createActionHunt (target);
		}
	}

	double relativeDifference (double v1, double v2) const
	{
		assert (v1 >= 0.0);
		assert (v2 >= 0.0);
		return (v1 - v2) / (v1 + v2) / 2; 
	}

	double inflictDamageWeightForAttacking (const Blob& b) const
	{
		return relativeDifference (damage (), b.HP ()) * 2.0;
	}

	double avoidDamageWeightForAttacking (const Blob& b) const
	{
		return relativeDifference (HP (), b.damage ()) * 2.0;
	}

	double avoidDamageWeightForFleeing (const Blob& b) const
	{
		return b.inflictDamageWeightForAttacking (*this);
	}

	double distanceWeight (const Blob& b) const
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

	double attackWeight (const Blob& b) const
	{
		return distanceWeight (b) * std::max (inflictDamageWeightForAttacking (b), avoidDamageWeightForAttacking (b));
	}	
	
	double fleeWeight (const Blob& b) const
	{
		return distanceWeight (b) * avoidDamageWeightForFleeing (b);
	}
	
	struct ActionPossibility 
	{
		enum {attack, flee} action;
		double weight;
		Blob* target;
	};

	std::vector<ActionPossibility> findPossibleActions (std::vector<Blob>& others) const
	{	
		std::vector <ActionPossibility> possibilities;

		for (auto& b : others)
		{
			if ((&b != this) && !b.isDead ())
			{
				double a = _aggressionFn (_aggression);

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

	std::vector<Pt<double>> _points;

	std::string _name;
	double _speed;
        double _runningSpeed;
	double _smell;
	unsigned int _maxHP;
	unsigned int _HP;
	unsigned int _endurance;
	double _aggression;
	unsigned int _lifespan;
	unsigned int _damage;

	double _previousAngleInRadians = 0;

	std::string _state;

	unsigned int _fatigue;
	bool _tired;

	unsigned int _age;	
	bool _dead;

	std::function<double(double)> _moveDirectionFn;
	std::function<double(double)> _aggressionFn;
};

inline std::ostream& operator<< (std::ostream& s, const Blob& b)
{
	s << b.x () << "," << b.y ();
	return s; 
}

#endif

