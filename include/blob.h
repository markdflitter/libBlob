#include "pt.h"
#include <functional>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <random>

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

class Blob;

class Movement 
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
	Blob (std::function<double (double)> rnd, double x, double y, double speed, double smell) :
		_rnd (rnd), _p (x, y), _speed (speed), _smell (smell)
	{
	}

	friend std::ostream& operator<<(std::ostream& s, const Blob& b);

	double x () const {return _p.x ();}
	double y () const {return _p.y ();}

	double distance (const Blob& other) const
	{
		double dx = -_p.x () + other.x ();
		double dy = -_p.y () + other.y ();
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

        void move (double speed, double angleInRadians) 
	{
		_previousAngleInRadians = angleInRadians;

		double denormalisedMoveDirection = _previousAngleInRadians - M_PI / 2;
		_p.x () += speed * cos (denormalisedMoveDirection);
		_p.y () += speed * sin (denormalisedMoveDirection);
	}

        Movement wander (const std::vector<Blob>& others)
        {
		double angle = _rnd (_previousAngleInRadians);
		return Movement (this, "wandering", _speed, angle);
	}

	Movement chooseNextAction (const std::vector<Blob>& others)
	{
		return wander (others);
	}

	std::string parms () const 
	{
		std::stringstream ss;

		ss << _speed << "," << _smell << "," << 360 * _previousAngleInRadians / (2 * M_PI);
		
		return ss.str ();
	}

/*
	void move (const Blob& other) {
		double dx = -_p.x () + other.x ();
		double dy = -_p.y () + other.y ();
		double d = sqrt ((dx * dx) + (dy * dy)) / 100.0;

//		std::cout << d << ",";

		if (_dead) {
			std::cout << "dead,";
			return;
		}

		bool can_smell = d < (_smell);

		if ((sqrt (d) < 1) && _c) {
			_dead = true;    
//			std::cout << "dying,";
		}
		else if (can_smell && _a) {
			_previousAngleInRadians = atan2 (dy,dx); 

			_p.x () += _speed * cos (_previousAngleInRadians);
			_p.y () += _speed * sin (_previousAngleInRadians);
//			std::cout << "hunting,";
		}
		else if (can_smell && _c) {
			_previousAngleInRadians = atan2 (dy,dx) + M_PI; 

			_p.x () += _speed * cos (_previousAngleInRadians);
			_p.y () += _speed * sin (_previousAngleInRadians);
//			std::cout << "running,";
		}
		else {	
			float n = _rnd (_previousAngleInRadians);

			_p.x () += _speed * cos (n);
			_p.y () += _speed * sin(n);

			//    std::cout << _p.x () / 100 << ", " << _p.y () / 100  << '\n';

			_previousAngleInRadians = n;
//			std::cout << "wandering,";    
		}
	}
*/
private:
	std::function<double(double)> _rnd;
	Pt<double> _p;

	double _speed;
        double _smell;

	double _previousAngleInRadians = 0;
};

std::ostream& operator<< (std::ostream& s, const Blob& b)
{
	s << b.x () << "," << b.y ();
	return s; 
}

std::ostream& operator<< (std::ostream& s, const Movement& m)
{
	s << m._reason << "," << m._speed << "," << 360 * m._angleInRadians / (2 * M_PI);
	return s; 
}


void Movement::apply ()
{
	_blob->move (_speed, _angleInRadians);
}


