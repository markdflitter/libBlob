#ifndef INCLUDED_RND_H
#define INCLUDED_RND_H

#include <random>
#include <math.h>

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

#endif
