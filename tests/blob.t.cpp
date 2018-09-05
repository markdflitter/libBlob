#include <gtest/gtest.h>
#include <random>
#include <blob.h>

constexpr double threshold = 0.00001;

double fixed_angle (double previousMoveDirection)
{
	return previousMoveDirection + M_PI / 4;
};

TEST (Blob, create) 
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 100, 100, 200, 300};

	ASSERT_EQ (b1.name (), "mark");
	ASSERT_EQ (b1.x (), 10.1);
	ASSERT_EQ (b1.y (), 20.2);
	ASSERT_EQ (b1.speed (), 100);
	ASSERT_EQ (b1.smell (), 200);
	ASSERT_EQ (b1.strength (), 300);
	ASSERT_FALSE (b1.isDead ());

	Blob b2 {"annette", fixed_angle, -10.1, -20.2, 300, 300, 400, 500};

	ASSERT_EQ (b2.name (), "annette");
	ASSERT_EQ (b2.x (), -10.1);
	ASSERT_EQ (b2.y (), -20.2);
	ASSERT_EQ (b2.speed (), 300);
	ASSERT_EQ (b2.smell (), 400);
	ASSERT_EQ (b2.strength (), 500);
	ASSERT_FALSE (b2.isDead ());
}

TEST (Blob, distance0)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, 10, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 0);
	ASSERT_EQ (b2.distance (b1), 0);
}

TEST (Blob, distance345)
{
	Blob b1 {"mark", fixed_angle, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 3, 4, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distancen345)
{
	Blob b1 {"mark", fixed_angle, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, -3, -4, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distance345_2)
{
	Blob b1 {"mark", fixed_angle, 3, 4, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 6, 8, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, inRangex)
{
	Blob b1 {"mark", fixed_angle, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, 0, 0, 0, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 9));
	ASSERT_FALSE (b2.inRange (b1, 9));

	ASSERT_TRUE (b1.inRange (b2, 10));
	ASSERT_TRUE (b2.inRange (b1, 10));
}

TEST (Blob, inRangey)
{
	Blob b1 {"mark", fixed_angle, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 0, 10, 0, 0, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 9));
	ASSERT_FALSE (b2.inRange (b1, 9));

	ASSERT_TRUE (b1.inRange (b2, 10));
	ASSERT_TRUE (b2.inRange (b1, 10));
}

TEST (Blob, inRangexy)
{
	Blob b1 {"mark", fixed_angle, 3, 4, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 6, 8, 0, 0, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 4));
	ASSERT_FALSE (b2.inRange (b1, 4));

	ASSERT_TRUE (b1.inRange (b2, 5));
	ASSERT_TRUE (b2.inRange (b1, 5));
}

TEST (Blob, sameSquareTrue)
{
	Blob b1 {"mark", fixed_angle, 10, 20, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, 20, 0, 0, 0, 0};

	ASSERT_TRUE (b1.sameSquare (b2));
	ASSERT_TRUE (b2.sameSquare (b1));
}

TEST (Blob, sameSquareFalse)
{
	Blob b1 {"mark", fixed_angle, 10, 20, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 20, 10, 0, 0, 0, 0};

	ASSERT_FALSE (b1.sameSquare (b2));
	ASSERT_FALSE (b2.sameSquare (b1));
}

TEST (Blob, canSmellTrue)
{
	Blob b1 {"mark", fixed_angle, 3, 4, 100, 100, 5, 0};
	Blob b2 {"annette", fixed_angle, 6, 8, 100, 100, 5, 0};

	ASSERT_TRUE (b1.canSmell (b2));
	ASSERT_TRUE (b2.canSmell (b1));
}

TEST (Blob, canSmellFalse)
{
	Blob b1 {"mark", fixed_angle, 3, 4, 0, 0, 4, 0};
	Blob b2 {"annette", fixed_angle, 6, 8, 0, 0, 4, 0};

	ASSERT_FALSE (b1.canSmell (b2));
	ASSERT_FALSE (b2.canSmell (b1));
}

TEST (Blob, canSmellBoth)
{
	Blob b1 {"mark", fixed_angle, 3, 4, 0, 0, 4, 0};
	Blob b2 {"annette", fixed_angle, 6, 8, 0, 0, 5, 0};

	ASSERT_FALSE (b1.canSmell (b2));
	ASSERT_TRUE (b2.canSmell (b1));
}

TEST (Blob, angleN)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 5, 10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 0.0f) < threshold);
}

TEST (Blob, angleS)
{
	Blob b1 {"mark", fixed_angle, -5, -5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, -5, -10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - M_PI) < threshold);
}

TEST (Blob, angleE)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, 5, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - M_PI / 2) < threshold);
}

TEST (Blob, angleW)
{
	Blob b1 {"mark", fixed_angle, -5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, -10, 5, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 3*M_PI/2) < threshold);
}

TEST (Blob, angleNE)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, 10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - M_PI/4) < threshold);
}

TEST (Blob, angleNW)
{
	Blob b1 {"mark", fixed_angle, -5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, -10, 10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - -M_PI/4) < threshold);
}

TEST (Blob, angleSE)
{
	Blob b1 {"mark", fixed_angle, 5, -5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, -10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 3 * M_PI/4) < threshold);
}

TEST (Blob, angleSW)
{
	Blob b1 {"mark", fixed_angle, -5, -5, 0, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, -10, -10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 5 * M_PI/4) < threshold);
}

TEST(Blob, kill)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 0, 0, 0, 0};
	b1.kill ();

	ASSERT_TRUE (b1.isDead ());
	ASSERT_TRUE (b1.state () == "dead");
}
	
TEST (Blob, moveN)
{
	Blob b1 {"mark", fixed_angle, 10.1, 15.2, 5, 5, 0, 0};
	b1.move (5, 0, "N");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "N");
}

TEST (Blob, moveFast)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (10, 0, "N");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 30.2) < threshold);
	ASSERT_TRUE (b1.state () == "N");
}

TEST (Blob, moveS)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, M_PI, "S");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 15.2) < threshold);
	ASSERT_TRUE (b1.state () == "S");

	b1.move (5, -M_PI, "S");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 10.2) < threshold);
	ASSERT_TRUE (b1.state () == "S");
}


TEST (Blob, moveE)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, M_PI / 2, "E");

	ASSERT_TRUE (fabs (b1.x () - 15.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "E");
}

TEST (Blob, moveW)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, 3 * M_PI / 2, "W");

	ASSERT_TRUE (fabs (b1.x () - 5.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "W");

	b1.move (5, -M_PI / 2, "W");

	ASSERT_TRUE (fabs (b1.x () - 0.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "W");
}

TEST (Blob, moveNE)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, M_PI / 4,"NE");

	ASSERT_TRUE (fabs (b1.x () - 13.635533905932737) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 23.735533905932737) < threshold);
	ASSERT_TRUE (b1.state () == "NE");
}

TEST (Blob, moveNW)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, -M_PI / 4, "NW");

	ASSERT_TRUE (fabs (b1.x () - 06.564466094067262) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 23.735533905932737) < threshold);
	ASSERT_TRUE (b1.state () == "NW");

	Blob b2 {"annette", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b2.move (5, 7 * M_PI / 4, "NW");
	
	ASSERT_TRUE (fabs (b2.x () - 06.56446609406726) < threshold);
	ASSERT_TRUE (fabs (b2.y () - 23.73553390593273) < threshold);
	ASSERT_TRUE (b1.state () == "NW");
}

TEST (Blob, moveSE)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, 3 * M_PI / 4, "SE");

	ASSERT_TRUE (fabs (b1.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 16.66446609406726) < threshold);
	ASSERT_TRUE (b1.state () == "SE");
}

TEST (Blob, moveSW)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, 5 * M_PI / 4, "SW");

	ASSERT_TRUE (fabs (b1.x () - 06.56446609406726) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 16.66446609406726) < threshold);
	ASSERT_TRUE (b1.state () == "SW");

	Blob b2 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b2.move (5, -3 * M_PI / 4, "SW");

	ASSERT_TRUE (fabs (b2.x () - 06.56446609406726) < threshold);
	ASSERT_TRUE (fabs (b2.y () - 16.66446609406726) < threshold);
	ASSERT_TRUE (b1.state () == "SW");
}

TEST (Blob, moveNegativeX)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (20, 3 * M_PI / 2, "-x");

	ASSERT_TRUE (fabs (b1.x () - -9.9) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "-x");
}

TEST (Blob, moveNegativeY)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (30, M_PI, "-y");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - -9.8) < threshold);
	ASSERT_TRUE (b1.state () == "-y");
}


TEST (Blob, history)
{
	Blob b1 {"mark", fixed_angle, 10, 20, 5, 5, 0, 0};
	b1.move (5, M_PI, "N");
	b1.move (5, M_PI, "N");
	b1.move (5, M_PI / 2, "E");

	std::vector<Pt<double>> history = b1.history ();
	ASSERT_TRUE (history.size () == 4);
	ASSERT_TRUE (history[0].x () == 10);
 	ASSERT_TRUE (history[0].y () == 20);
	ASSERT_TRUE (history[1].x () == 10);
 	ASSERT_TRUE (history[1].y () == 15);
	ASSERT_TRUE (history[2].x () == 10);
 	ASSERT_TRUE (history[2].y () == 10);
	ASSERT_TRUE (history[3].x () == 15);
 	ASSERT_TRUE (history[3].y () == 10);
}

TEST (Blob, history_length)
{
	Blob b1 {"mark", fixed_angle, 10, 20, 5, 5, 0, 0};
	for (int i = 0; i < 1000; i++)
	{
		b1.move (5, 0, "N");
	}
	
	std::vector<Pt<double>> history = b1.history ();
	ASSERT_TRUE (history.size () == 500);
	
	ASSERT_TRUE (history[0].x () == 10);
 	ASSERT_TRUE (history[0].y () == 2525);
	
	ASSERT_TRUE (history[499].x () == 10);
 	ASSERT_TRUE (history[499].y () == 5020);
}

TEST (Blob, movement)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	std::shared_ptr<Action> m (new Movement (&b1, "because", 5.0, 0.0));
        m->apply ();
	
	ASSERT_EQ (b1.x (), 10.1);
	ASSERT_EQ (b1.y (), 25.2);
	ASSERT_TRUE (b1.state () == "because");
}

TEST (fixed_angle, isFixed)
{
	for (int i = 0; i < 8; i++)
	{
		ASSERT_TRUE (fabs (fixed_angle(i * M_PI/4) - ((i * M_PI / 4) + M_PI/4)) < threshold);
	}
}

TEST (Blob, usesFixedAngle)
{
	Blob b {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};

	for (int step = 1; step <= 8; step++)
	{
		std::shared_ptr<Action> a = b.wander ();
		ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
		std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
		ASSERT_EQ (m->_reason, "wandering");
		ASSERT_EQ (m->_speed, 5);
		ASSERT_TRUE (fabs (m->_angleInRadians - step * (M_PI / 4)) < threshold);
		m->apply ();
	}
}

TEST (Blob, wandering)
{
/*
13.635533905932700	23.735533905932700
18.635533905932700	23.735533905932700
22.171067811865500	20.200000000000000
22.171067811865500	15.200000000000000
18.635533905932700	11.664466094067300
13.635533905932700	11.664466094067300
10.100000000000000	15.200000000000000
10.100000000000000	20.200000000000000
*/

	Blob b {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0.0, 0};

	std::shared_ptr<Action> a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, M_PI / 4));
	a->apply ();
        ASSERT_TRUE (fabs (b.x () - 13.6355339059327) < threshold);
	ASSERT_TRUE (fabs (b.y () - 23.7355339059327) < threshold);

	a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
       	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, M_PI / 2));
	a->apply ();
	ASSERT_TRUE (fabs (b.x () - 18.6355339059327) < threshold);
	ASSERT_TRUE (fabs (b.y () - 23.7355339059327) < threshold);

	a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, 3 * M_PI / 4));
	a->apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, M_PI));
	a->apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 15.2) < threshold);

	a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, 5 * M_PI / 4));
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 18.63553390593270) < threshold);
	ASSERT_TRUE (fabs (b.y () - 11.66446609406730) < threshold);

	a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, 3 * M_PI / 2));
	a->apply ();
        ASSERT_TRUE (fabs (b.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b.y () - 11.66446609406730) < threshold);
	
	a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, 7 * M_PI / 4));
	a->apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 15.2) < threshold);

	a = b.wander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (*m  == Movement (&b, "wandering", 5, 2 * M_PI));
	a->apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);
}


TEST (Blob, huntN)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 2, 4, 0, 0};
	Blob b2 {"annette", fixed_angle, 5, 10, 12, 12, 0, 0};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette", 4, 0));
}

TEST (Blob, huntS)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 2, 4, 0, 0};
	Blob b2 {"annette", fixed_angle, 5, -10, 12, 12, 0, 0};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette", 4, M_PI));
}

TEST (Blob, huntE)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 2, 4, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, 5, 12, 12, 0, 0};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette", 4, M_PI/2));
}

TEST (Blob, huntW)
{
	Blob b1 {"mark", fixed_angle, -5, 5, 2, 4, 0, 0};
	Blob b2 {"annette", fixed_angle, -10, 5, 12, 12, 0, 0};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette", 4, 3 * M_PI / 2));
}

TEST (Blob, huntGetsCloser)
{
	Blob b1 {"mark", fixed_angle, -5, 5, 7, 7, 0, 0};
	Blob b2 {"annette", fixed_angle, -10, 5, 12, 12, 0, 0};

	double d1 = b1.distance (b2);
	std::shared_ptr<Action> m = b1.hunt (b2);
	m->apply ();

	double d2 = b1.distance (b2);
	ASSERT_TRUE (d2 < d1);
}

TEST (Blob, huntCatches)
{
	Blob b1 {"mark", fixed_angle, -5, 5, 7, 7, 0, 0};
	Blob b2 {"annette", fixed_angle, -10, 5, 12, 12, 0, 0};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr<Movement> m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (m->_speed < 7);
	a->apply ();

	ASSERT_TRUE (b1.sameSquare (b2));
}

TEST (Blob, attack)
{
	Blob b1 {"mark", fixed_angle, -5, 5, 7, 7, 0, 100};
	Blob b2 {"annette", fixed_angle, -10, 5, 12, 12, 0, 10};

	std::shared_ptr <Action> a = b2.attack (b1);
	a->apply ();

	ASSERT_TRUE (b1.strength () == 90);
}


TEST (Blob, choose_to_wander)
{
/*
13.635533905932700	23.735533905932700
18.635533905932700	23.735533905932700
22.171067811865500	20.200000000000000
22.171067811865500	15.200000000000000
18.635533905932700	11.664466094067300
13.635533905932700	11.664466094067300
10.100000000000000	15.200000000000000
10.100000000000000	20.200000000000000
*/
	Blob b {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0};
	std::vector<Blob> blobs;
	
	std::shared_ptr<Action> m = b.chooseNextAction (blobs);
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b.y () - 23.73553390593270) < threshold);

	m = b.chooseNextAction (blobs);
        m->apply ();
	ASSERT_TRUE (fabs (b.x () - 18.63553390593270) < threshold);
	ASSERT_TRUE (fabs (b.y () - 23.73553390593270) < threshold);
	
	m = b.chooseNextAction (blobs);
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	m = b.chooseNextAction (blobs);
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 15.2) < threshold);

	m = b.chooseNextAction (blobs);
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 18.63553390593270) < threshold);
	ASSERT_TRUE (fabs (b.y () - 11.66446609406730) < threshold);

	m = b.chooseNextAction (blobs);
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b.y () - 11.66446609406730) < threshold);

	m = b.chooseNextAction (blobs);
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 15.2) < threshold);
	
	m = b.chooseNextAction (blobs);
	m->apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);
}

TEST (Blob, choosesToHunt)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 10, 100, 1};
	Blob b2 {"annette", fixed_angle, 20, 20, 5, 5, 100, 0};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&blobs.front (), "hunting annette", 10, M_PI/4)); 
}


TEST (Blob, choosesClosestToHunt)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 10, 1000, 1};
	Blob b2 {"annette", fixed_angle, 20, 20, 5, 5, 1000, 0};
	Blob b3 {"duncan", fixed_angle, 25, 25, 5, 5, 1000, 0};
	std::vector <Blob> blobs {b1, b2, b3};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (*m == Movement (&blobs.front (), "hunting annette", 10, M_PI/4)); 
}

TEST (Blob, chooses_not_to_fight)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 0, 0};
	Blob b2 {"annette", fixed_angle, 20, 20, 5, 5, 0, 0};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, will_not_fight_self)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 1000, 0};
	std::vector <Blob> blobs {b1};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, will_not_fight_stronger)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 0, 0};
	Blob b2 {"annette", fixed_angle, 10, 10, 5, 5, 0, 100};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "running from annette");
}

TEST (Blob, chooses_not_to_fight_dead)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", fixed_angle, 10, 10, 5, 5, 0, 0};
	std::vector <Blob> blobs {b1, b2};
	
	blobs.back().kill ();
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, chooses_to_fight)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", fixed_angle, 10, 10, 5, 5, 0, 2};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Attack> (a));
	std::shared_ptr <Attack> m (std::dynamic_pointer_cast <Attack> (a));
	
	ASSERT_TRUE (m->_target == &blobs[1]);
	ASSERT_TRUE (m->_strength == 10);
}

TEST (Blob, chooses_to_fight_weakest)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", fixed_angle, 10, 10, 5, 5, 0, 2};
	Blob b3 {"duncan", fixed_angle, 10, 10, 5, 5, 0, 3};
	std::vector <Blob> blobs {b1, b2, b3};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Attack> (a));
	std::shared_ptr <Attack> m (std::dynamic_pointer_cast <Attack> (a));
	
	ASSERT_TRUE (m->_target == &blobs[1]);
	ASSERT_TRUE (m->_strength == 10);
}

TEST (Blob, actually_fights_and_kills)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", fixed_angle, 10, 10, 5, 5, 0, 2};
	std::vector <Blob> blobs {b1, b2};
	
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
		a->apply ();
	}
	ASSERT_TRUE (blobs[1].isDead ());
}


TEST (Blob, seededNormalDistributionInDegrees)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0, 40};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (dist (gen) );
	};

	ASSERT_EQ (int (rnd_angle (0.0)), 44);
	ASSERT_EQ (int (rnd_angle (0.0)), 12);
	ASSERT_EQ (int (rnd_angle (0.0)), 2);
	ASSERT_EQ (int (rnd_angle (0.0)), 2);
	ASSERT_EQ (int (rnd_angle (0.0)), -56);
	ASSERT_EQ (int (rnd_angle (0.0)), 60);
}

TEST (Blob, seededNormalDistributionInDegreesProgression)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0, 40};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + int(dist (gen) );
	};

	ASSERT_EQ (int (rnd_angle (0.0)), 44);
	ASSERT_EQ (int (rnd_angle (44.0)), 56);
	ASSERT_EQ (int (rnd_angle (56.0)), 58);
	ASSERT_EQ (int (rnd_angle (58.0)), 60);
	ASSERT_EQ (int (rnd_angle (60.0)), 4);
	ASSERT_EQ (int (rnd_angle (4.0)), 64);
}

TEST (Blob, seededNormalDistributionInRadians)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0, 40};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (2 * M_PI * dist (gen) / 360);
	};

        ASSERT_TRUE (fabs (rnd_angle (0.0) - 0.783859) < threshold);
        ASSERT_TRUE (fabs (rnd_angle (0.0) - 0.211398) < threshold);
        ASSERT_TRUE (fabs (rnd_angle (0.0) - 0.0494691) < threshold);
        ASSERT_TRUE (fabs (rnd_angle (0.0) - 0.0509925) < threshold);
        ASSERT_TRUE (fabs (rnd_angle (0.0) - -0.992971) < threshold);
	ASSERT_TRUE (fabs (rnd_angle (0.0) - 1.06121) < threshold);
	ASSERT_TRUE (fabs (rnd_angle (0.0) - -0.203431) < threshold);
}

TEST (Blob, choose_move_random_wander)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0, 40};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (2 * M_PI * dist (gen) / 360);
	};

	Blob b {"mark", rnd_angle, 10.1, 20.2, 5, 5, 0, 0};
	ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	std::vector<Blob> blobs;
	std::shared_ptr<Action> a = b.chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (fabs (m->_angleInRadians - 0.783859) < threshold);
}

TEST (Blob, move_random_wander)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0, 40};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (2 * M_PI * dist (gen) / 360);
	};

	Blob b {"mark", rnd_angle, 10.1, 20.2, 5, 5, 0, 0};
	ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	std::vector<Blob> blobs;
	std::shared_ptr<Action> m = b.chooseNextAction (blobs);
	m->apply ();
	ASSERT_TRUE (fabs (b.x () - 13.630087040) < threshold);
	ASSERT_TRUE (fabs (b.y () - 23.740972392) < threshold);

	m = b.chooseNextAction (blobs);
	m->apply ();
	ASSERT_TRUE (fabs (b.x () - 17.824580716) < threshold);
	ASSERT_TRUE (fabs (b.y () - 26.462410339) < threshold);
	
	m = b.chooseNextAction (blobs);
	m->apply ();
	ASSERT_TRUE (fabs (b.x () - 22.148524241) < threshold);
	ASSERT_TRUE (fabs (b.y () - 28.97310591453995698) < threshold);
}


TEST (Blob, attack_no_kill)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 100};
	
	b1.attacked (10);
	ASSERT_TRUE (b1.strength () == 90);
	ASSERT_TRUE (!b1.isDead ());
}

TEST (Blob, attack_and_kill)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 20};
	
	b1.attacked (10);
	ASSERT_TRUE (b1.strength () == 10);
	ASSERT_TRUE (!b1.isDead ());
	
	b1.attacked (10);
	ASSERT_TRUE (b1.strength () == 0);
	ASSERT_TRUE (b1.isDead ());
}

TEST (Blob, dead_blobs_do_nothing)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 100, 0};
	Blob b2 {"annette", fixed_angle, 10, 10, 5, 5, 100, 100};
	std::vector <Blob> blobs {b1, b2};
	
	blobs[0].kill ();
	
	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&blobs[0],"dead",0,0));
}

TEST (Blob, dead_blobs_are_not_hunted)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 100, 0};
	Blob b2 {"annette", fixed_angle, 10, 10, 5, 5, 100, 100};
	std::vector <Blob> blobs {b1, b2};
	
	blobs[0].kill ();

	std::shared_ptr<Action> a = blobs[1].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, flee)
{
	Blob b1 {"mark", fixed_angle, 10, 5, 2, 4, 0, 0};
	Blob b2 {"annette", fixed_angle, 5, 10, 12, 12, 0, 0};

	b1.move (5, 3 * M_PI/2, "wandering");	

	std::shared_ptr<Action> a = b1.flee (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_target == &b1);
	ASSERT_TRUE (m->_reason == "running from annette");
	ASSERT_TRUE (m->_speed == 4);
	ASSERT_TRUE (fabs (m->_angleInRadians) - ((0.9 * 3 * M_PI / 2) + (0.1 * M_PI) + M_PI / 4) < threshold);
}

TEST (Blob, does_not_run)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 2, 2, 0, 0};
	Blob b2 {"annette", fixed_angle, 5, 10, 12, 12, 0, 0};
	std::vector<Blob> blobs {b1,b2};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, does_not_run_from_dead_blobs)
{
	Blob b1 {"mark", fixed_angle, 5, 5, 2, 2, 0, 0};
	Blob b2 {"annette", fixed_angle, 5, 5, 12, 12, 0, 10};
	std::vector<Blob> blobs {b1,b2};
	
	blobs[1].kill ();

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, runs)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 1000, 0};
	Blob b2 {"annette", fixed_angle, 20, 20, 5, 5,0, 1};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "running from annette");
}

TEST (Blob, runs_from_strongest)
{
	Blob b1 {"mark", fixed_angle, 10, 10, 5, 5, 1000, 0};
	Blob b2 {"annette", fixed_angle, 20, 20, 5, 5, 0, 1};
	Blob b3 {"duncan", fixed_angle, 20, 20, 5, 5, 0, 2};
	std::vector <Blob> blobs {b1, b2, b3};

	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "running from duncan");
}

TEST (Blob, parms)
{
	Blob b {"mark", fixed_angle, 20, 40, 5, 10, 100, 22};
	std::shared_ptr<Action> a (new Movement (&b, "", 10.0, M_PI / 2));
	a->apply ();

	ASSERT_EQ (b.parms (), "alive,5,10,100,22,90");
}

TEST (Blob, output)
{
	Blob b {"mark", fixed_angle, 20, 40, 5, 5, 100, 0};
	std::shared_ptr<Action> a (new Movement (&b, "", 10.0, M_PI / 2));
	a->apply ();

	std::stringstream s;

	s << b;

	ASSERT_EQ (s.str (), "30,40");
}

TEST (Blob, independent)
{
	Blob b1 {"mark", Rnd (1, 40), 0, 0, 10, 10, 10, 0};
	Blob b2 {"annette", Rnd (1, 40), 0, 0, 10, 10, 10, 0};
	Blob b3 {"grace", Rnd (2, 40), 0, 0, 10, 10, 10, 0};
	
	std::vector<Blob> blobs;
	b1.chooseNextAction (blobs)->apply ();
	b2.chooseNextAction (blobs)->apply ();
	b3.chooseNextAction (blobs)->apply ();

	ASSERT_TRUE (fabs (b1.x () - b2.x ()) < threshold);
	ASSERT_TRUE (fabs (b1.y () - b2.y ()) < threshold);
	ASSERT_TRUE (fabs (b1.x () - b3.x ()) >= threshold);
	ASSERT_TRUE (fabs (b1.y () - b3.y ()) >= threshold);
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
