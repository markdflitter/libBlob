#ifndef INCLUDED_BLOB_H
#define INCLUDED_BLOB_H

#include "pt.h"
#include <functional>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <memory>

class Rnd 
{
public:
	Rnd (unsigned int seed, int stddev) :
		_gen (seed)
	     ,  _dist (0, stddev) 
	{
	}

	double operator ()(double previousMoveDirection) 
	{
		return previousMoveDirection + (2 * M_PI * _dist (_gen) / 360);
	}
private:
	std::mt19937 _gen;
	std::normal_distribution<> _dist;
};

class Action 
{
public:
	virtual ~Action () {};
	virtual void apply () = 0;
};

class Blob;

class Movement : public Action
{
	public:
		Movement (Blob* blob, const std::string& reason, double speed, double angleInRadians) :
			_blob (blob)
			, _reason (reason)
			, _speed (speed)
			, _angleInRadians (angleInRadians)
		{
		}

		Movement (const Movement& m) :
			_blob (m._blob)
			, _reason (m._reason)
			, _speed (m._speed)
			, _angleInRadians (m._angleInRadians)
		{
		}

		Movement (const Movement&& m) :
			_blob (m._blob)
			, _reason (m._reason)
			, _speed (m._speed)
			, _angleInRadians (m._angleInRadians)
		{
		}

		Movement& operator= (const Movement& m)
		{
			_blob  = m._blob;
			_reason = m._reason;
			_speed = m._speed;
			_angleInRadians = m._angleInRadians;

			return *this;
		}

		Movement& operator= (const Movement&& m)
		{
			_blob  = m._blob;
			_reason = m._reason;
			_speed = m._speed;
			_angleInRadians = m._angleInRadians;

			return *this;
		}

		bool operator== (const Movement& m) const
		{
			return (_blob == m._blob) 
				&& (_reason == m._reason)
				&& (_speed == m._speed)
				&& (_angleInRadians == m._angleInRadians);
		}	

		bool operator!= (const Movement& m) const
		{
			return (_blob != m._blob) 
				|| (_reason != m._reason)
				|| (_speed != m._speed)
				|| (_angleInRadians != m._angleInRadians);
		}

		void apply ();

		friend std::ostream& operator<< (std::ostream& s, const Movement& m);
	public:
		Blob* _blob;
		std::string _reason; 
		double _speed;
		double _angleInRadians;
};


class Blob {
public:
	Blob (const std::string& name, std::function<double (double)> rnd, double x, double y, double speed, double smell, double strength) :
		_name (name), _state ("newborn"), _rnd (rnd), _speed (speed), _smell (smell), _strength (strength), _dead (false)
	{
		_points.push_back (Pt<double> (x,y));
	}

	friend std::ostream& operator<<(std::ostream& s, const Blob& b);

	std::string name () const {return _name;}
	std::string state () const {return _state;}
	double x () const {return _points.back ().x ();}
	double y () const {return _points.back ().y ();}
	double speed () const {return _speed;}
	double smell () const {return _smell;}
	double strength () const {return _strength;}
	std::vector<Pt<double>> history () const {return _points;}
	void kill ()
	{
		_dead = true;
		_state = "dead";
	}

	bool isDead () const {return _dead;}

	double distance (const Blob& other) const
	{
		double dx = other.x () - x();
		double dy = other.y () - y();
		double d = sqrt ((dx * dx) + (dy * dy));

		return d; 
	}

	bool inRange (const Blob& other, int range) const
	{
		return distance (other) <= range;
	}

	bool sameSquare (const Blob& other) const
	{
		return inRange (other, 1);
	}

	bool canSmell (const Blob& other) const
	{
		return inRange (other, _smell);
	}

	double angle (const Blob& other) const
	{
		double dx = x () - other.x ();
		double dy = y () - other.y ();

		return atan2 (dy, -dx) + M_PI/2;
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
	}

        std::shared_ptr <Action> die ()
        {
		return std::shared_ptr<Action> (new Movement (this, "dead", 0, 0));
	}
 
        std::shared_ptr <Action> wander ()
        {
		double angle = _rnd (_previousAngleInRadians);
		return std::shared_ptr<Action> (new Movement (this, "wandering", _speed, angle));
	}
        
	std::shared_ptr <Action> hunt (const Blob& target)
        {
		return std::shared_ptr <Action> (new Movement (this,
				 "hunting " + target.name (),
				std::min (_speed, distance (target)),
				angle (target)));
	}

	std::shared_ptr <Action> chooseNextAction (const std::vector<Blob>& others)
	{
		if (isDead())
			return die ();

		std::vector <std::pair <double, Blob>> huntTargets;
		for (auto& b : others)
		{
			if ((&b != this) && canSmell (b) && !b.isDead () && (b.strength () < _strength))
			{
				double weight = 1.0 - (distance (b) / _smell);
				huntTargets.push_back (std::make_pair (weight, b));
			}
		}	
		std::sort (huntTargets.begin (), huntTargets.end (),
			   [] (const std::pair <double, Blob>& lhs,
			       std::pair <double, Blob>& rhs) {return lhs.first < rhs.first;});
		
		return huntTargets.size () > 0 ? hunt (huntTargets.back ().second) : wander ();
	}


	void fight (std::vector <Blob>& others)
	{
		if (isDead ()) 
			return;

		for (auto& b : others)
		{
			if (b.isDead ()) 
				continue;

			if ((&b != this) && sameSquare (b))
			{
				if (_strength > b._strength)
				{
					b.kill ();
				}
				else if (b._strength > _strength)
				{
					kill ();
				}
			}
		}
	}

	std::string parms () const 
	{
		std::stringstream ss;

		ss << (isDead () ? "dead" : "alive") << "," <<_speed << "," << _smell << "," << _strength << "," << 360 * _previousAngleInRadians / (2 * M_PI);
		
		return ss.str ();
	}
private:
	std::function<double(double)> _rnd;
	std::vector<Pt<double>> _points;

	std::string _name;
	std::string _state;
	double _speed;
        double _smell;
	double _strength;

	bool _dead;
	double _previousAngleInRadians = 0;
};

inline std::ostream& operator<< (std::ostream& s, const Blob& b)
{
	s << b.x () << "," << b.y ();
	return s; 
}

inline std::ostream& operator<< (std::ostream& s, const Movement& m)
{
	s << m._reason << "," << m._speed << "," << 360 * m._angleInRadians / (2 * M_PI);
	return s; 
}


inline void Movement::apply ()
{
	_blob->move (_speed, _angleInRadians, _reason);
}

#endif
