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
	Blob b1 {fixed_angle, 10.1, 20.2, 0, 0};

	ASSERT_EQ (b1.x (), 10.1);
	ASSERT_EQ (b1.y (), 20.2);

	Blob b2 {fixed_angle, -10.1, -20.2, 0, 0};

	ASSERT_EQ (b2.x (), -10.1);
	ASSERT_EQ (b2.y (), -20.2);
}

TEST(Movement, equal)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 0, 0};
	Blob b2 {fixed_angle, 10.1, 20.2, 0, 0};

	Movement m (&b1, "a", 10, 20);
	ASSERT_TRUE (m == m);

	Movement m1 (&b1, "b", 10, 20);
	ASSERT_FALSE (m == m1);

	Movement m2 (&b1, "a", 30, 20);
	ASSERT_FALSE (m == m2);

	Movement m3 (&b1, "a", 10, 40);
	ASSERT_FALSE (m == m3);

	Movement m4 (&b2, "a", 10, 20);
	ASSERT_FALSE (m == m4);
}

TEST(Movement, not_equal)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 0, 0};
	Blob b2 {fixed_angle, 10.1, 20.2, 0, 0};

	Movement m (&b1, "a", 10, 20);
	ASSERT_FALSE (m != m);

	Movement m1 (&b1, "b", 10, 20);
	ASSERT_TRUE (m != m1);

	Movement m2 (&b1, "a", 30, 20);
	ASSERT_TRUE (m != m2);

	Movement m3 (&b1, "a", 10, 40);
	ASSERT_TRUE (m != m3);

	Movement m4 (&b2, "a", 10, 20);
	ASSERT_TRUE (m != m4);
}


TEST(Movement, copy_construct)
{
  	Blob b1 {fixed_angle, 10.1, 20.2, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (m);

	ASSERT_EQ (m,m2);
}

TEST(Movement, move_construct)
{
  	Blob b1 {fixed_angle, 10.1, 20.2, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (Movement (&b1, "a", 10, 20));
	
	ASSERT_EQ (m, m2);
}

TEST(Movement, assign)
{
  	Blob b1 {fixed_angle, 10.1, 20.2, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (&b1, "c", 10, 20);
	m2 = m;
	
	ASSERT_EQ (m, m2);
}

TEST(Movement, move_assign)
{
  	Blob b1 {fixed_angle, 10.1, 20.2, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (&b1, "c", 10, 20);
	m2 = Movement (&b1, "a", 10, 20);
	
	ASSERT_EQ (m, m2);
}

TEST (Blob, distance0)
{
	Blob b1 {fixed_angle, 10, 10, 0, 0};
	Blob b2 {fixed_angle, 10, 10, 0, 0};

	ASSERT_EQ (b1.distance (b2), 0);
	ASSERT_EQ (b2.distance (b1), 0);
}

TEST (Blob, distance345)
{
	Blob b1 {fixed_angle, 0, 0, 0, 0};
	Blob b2 {fixed_angle, 3, 4, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distancen345)
{
	Blob b1 {fixed_angle, 0, 0, 0, 0};
	Blob b2 {fixed_angle, -3, -4, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distance345_2)
{
	Blob b1 {fixed_angle, 3, 4, 0, 0};
	Blob b2 {fixed_angle, 6, 8, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, inRangex)
{
	Blob b1 {fixed_angle, 0, 0, 0, 0};
	Blob b2 {fixed_angle, 10, 0, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 9));
	ASSERT_FALSE (b2.inRange (b1, 9));

	ASSERT_TRUE (b1.inRange (b2, 10));
	ASSERT_TRUE (b2.inRange (b1, 10));
}

TEST (Blob, inRangey)
{
	Blob b1 {fixed_angle, 0, 0, 0, 0};
	Blob b2 {fixed_angle, 0, 10, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 9));
	ASSERT_FALSE (b2.inRange (b1, 9));

	ASSERT_TRUE (b1.inRange (b2, 10));
	ASSERT_TRUE (b2.inRange (b1, 10));
}

TEST (Blob, inRangexy)
{
	Blob b1 {fixed_angle, 3, 4, 0, 0};
	Blob b2 {fixed_angle, 6, 8, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 4));
	ASSERT_FALSE (b2.inRange (b1, 4));

	ASSERT_TRUE (b1.inRange (b2, 5));
	ASSERT_TRUE (b2.inRange (b1, 5));
}

TEST (Blob, sameSquareTrue)
{
	Blob b1 {fixed_angle, 10, 20, 0, 0};
	Blob b2 {fixed_angle, 10, 20, 0, 0};

	ASSERT_TRUE (b1.sameSquare (b2));
	ASSERT_TRUE (b2.sameSquare (b1));
}

TEST (Blob, sameSquareFalse)
{
	Blob b1 {fixed_angle, 10, 20, 0, 0};
	Blob b2 {fixed_angle, 20, 10, 0, 0};

	ASSERT_FALSE (b1.sameSquare (b2));
	ASSERT_FALSE (b2.sameSquare (b1));
}

TEST (Blob, canSmellTrue)
{
	Blob b1 {fixed_angle, 3, 4, 100, 5};
	Blob b2 {fixed_angle, 6, 8, 100, 5};

	ASSERT_TRUE (b1.canSmell (b2));
	ASSERT_TRUE (b2.canSmell (b1));
}

TEST (Blob, canSmellFalse)
{
	Blob b1 {fixed_angle, 3, 4, 0, 4};
	Blob b2 {fixed_angle, 6, 8, 0, 4};

	ASSERT_FALSE (b1.canSmell (b2));
	ASSERT_FALSE (b2.canSmell (b1));
}

TEST (Blob, canSmellBoth)
{
	Blob b1 {fixed_angle, 3, 4, 0, 4};
	Blob b2 {fixed_angle, 6, 8, 0, 5};

	ASSERT_FALSE (b1.canSmell (b2));
	ASSERT_TRUE (b2.canSmell (b1));
}

TEST (Blob, moveN)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (5, 0);

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 15.2) < threshold);
}

TEST (Blob, moveFast)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (10, 0);

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 10.2) < threshold);
}

TEST (Blob, moveS)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (5, M_PI);

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 25.2) < threshold);

	b1.move (5, -M_PI);

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 30.2) < threshold);
}

TEST (Blob, moveE)
{
	Blob b1 {fixed_angle, 10.1, 20.2,5 , 0};
	b1.move (5, M_PI / 2);

	ASSERT_TRUE (fabs (b1.x () - 15.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
}

TEST (Blob, moveW)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (5, 3 * M_PI / 2);

	ASSERT_TRUE (fabs (b1.x () - 5.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);

	b1.move (5, -M_PI / 2);

	ASSERT_TRUE (fabs (b1.x () - 0.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
}

TEST (Blob, moveNE)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (5, M_PI / 4);

	ASSERT_TRUE (fabs (b1.x () - 13.635533905932737) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 16.664466094067262) < threshold);
}

TEST (Blob, moveNW)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (5, -M_PI / 4);

	ASSERT_TRUE (fabs (b1.x () - 06.564466094067262) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 16.664466094067262) < threshold);

	Blob b2 {fixed_angle, 10.1, 20.2, 5, 0};
	b2.move (5, 7 * M_PI / 4);
	
	ASSERT_TRUE (fabs (b2.x () - 06.564466094067262) < threshold);
	ASSERT_TRUE (fabs (b2.y () - 16.664466094067262) < threshold);
}

TEST (Blob, moveSE)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (5, 3 * M_PI / 4);

	ASSERT_TRUE (fabs (b1.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 23.73553390593273) < threshold);
}

TEST (Blob, moveSW)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (5, 5 * M_PI / 4);

	ASSERT_TRUE (fabs (b1.x () - 06.564466094067262) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 23.73553390593273) < threshold);
	
	Blob b2 {fixed_angle, 10.1, 20.2, 5, 0};
	b2.move (5, -3 * M_PI / 4);

	ASSERT_TRUE (fabs (b2.x () - 06.564466094067262) < threshold);
	ASSERT_TRUE (fabs (b2.y () - 23.73553390593273) < threshold);
}

TEST (Blob, moveNegativeX)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (20, 3 * M_PI / 2);

	ASSERT_TRUE (fabs (b1.x () - -9.9) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
}

TEST (Blob, moveNegativeY)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	b1.move (30, 0);

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - -9.8) < threshold);
}


TEST (Blob, history)
{
	Blob b1 {fixed_angle, 10, 20, 5, 0};
	b1.move (5, 0);
	b1.move (5, 0);
	b1.move (5, M_PI / 2);

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
	Blob b1 {fixed_angle, 10, 20, 5, 0};
	for (int i = 0; i < 200; i++)
	{
		b1.move (5, 0);
	}
	
	std::vector<Pt<double>> history = b1.history ();
	ASSERT_TRUE (history.size () == 100);
	
	ASSERT_TRUE (history[0].x () == 10);
 	ASSERT_TRUE (history[0].y () == -485);
	
	ASSERT_TRUE (history[99].x () == 10);
 	ASSERT_TRUE (history[99].y () == -980);

}

TEST (Blob, movement)
{
	Blob b1 {fixed_angle, 10.1, 20.2, 5, 0};
	Movement m (&b1, "", 5.0, 0.0);
        m.apply ();
	
	ASSERT_EQ (b1.x (), 10.1);
	ASSERT_EQ (b1.y (), 15.2);
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
	Blob b {fixed_angle, 10.1, 20.2, 5, 0};

	for (int step = 1; step <= 8; step++)
	{
		Movement m = b.wander (std::vector <Blob> {});
		ASSERT_EQ (m._reason, "wandering");
		ASSERT_EQ (m._speed, 5);

		ASSERT_TRUE (fabs (m._angleInRadians - step * (M_PI / 4)) < threshold);
		m.apply ();
	}
}

TEST (Blob, wandering)
{
	Blob b {fixed_angle, 10.1, 20.2, 5, 0};

	Movement m = b.wander (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b.y () - 16.66446609406730) < threshold);

	m = b.wander (std::vector <Blob> {});
        m.apply ();
	ASSERT_TRUE (fabs (b.x () - 18.63553390593270) < threshold);
	ASSERT_TRUE (fabs (b.y () - 16.66446609406730) < threshold);

	m = b.wander (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	m = b.wander (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 25.2) < threshold);

	m = b.wander (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 18.63553390593270) < threshold);
	ASSERT_TRUE (fabs (b.y () - 28.73553390593270) < threshold);

	m = b.wander (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b.y () - 28.7355339059327) < threshold);

	m = b.wander (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 25.2) < threshold);

	m = b.wander (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);
}

TEST (Blob, choose_to_wander)
{
	Blob b {fixed_angle, 10.1, 20.2, 5, 0};

	Movement m = b.chooseNextAction (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b.y () - 16.66446609406730) < threshold);

	m = b.chooseNextAction (std::vector <Blob> {});
        m.apply ();
	ASSERT_TRUE (fabs (b.x () - 18.63553390593270) < threshold);
	ASSERT_TRUE (fabs (b.y () - 16.66446609406730) < threshold);

	m = b.chooseNextAction (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	m = b.chooseNextAction (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 22.17106781186550) < threshold);
	ASSERT_TRUE (fabs (b.y () - 25.2) < threshold);

	m = b.chooseNextAction (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 18.63553390593270) < threshold);
	ASSERT_TRUE (fabs (b.y () - 28.73553390593270) < threshold);

	m = b.chooseNextAction (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b.y () - 28.7355339059327) < threshold);

	m = b.chooseNextAction (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 25.2) < threshold);

	m = b.chooseNextAction (std::vector <Blob> {});
	m.apply ();
        ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);
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

	Blob b {rnd_angle, 10.1, 20.2, 5, 0};
	ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	Movement m = b.chooseNextAction (std::vector<Blob> {});
	ASSERT_TRUE (fabs (m._angleInRadians - 0.783859) < threshold);
}

TEST (Blob, move_random_wander)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0, 40};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (2 * M_PI * dist (gen) / 360);
	};

	Blob b {rnd_angle, 10.1, 20.2, 5, 0};
	ASSERT_TRUE (fabs (b.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b.y () - 20.2) < threshold);

	Movement m = b.chooseNextAction (std::vector<Blob> {});
	m.apply ();
	ASSERT_TRUE (fabs (b.x () - 13.630087040) < threshold);
	ASSERT_TRUE (fabs (b.y () - 16.659027607) < threshold);

	m = b.chooseNextAction (std::vector<Blob> {});
	m.apply ();
	ASSERT_TRUE (fabs (b.x () - 17.824580716) < threshold);
	ASSERT_TRUE (fabs (b.y () - 13.937589972) < threshold);
	
	m = b.chooseNextAction (std::vector<Blob> {});
	m.apply ();
	ASSERT_TRUE (fabs (b.x () - 22.148524241) < threshold);
	ASSERT_TRUE (fabs (b.y () - 11.426894803) < threshold);
}


TEST (Blob, parms)
{
  Blob b {fixed_angle, 20, 40, 5, 100};
  Movement m (&b, "", 10.0, M_PI / 2);
  m.apply ();

  ASSERT_EQ (b.parms (), "5,100,90");
}

TEST (Blob, output)
{
  Blob b {fixed_angle, 20, 40, 5, 100};
  Movement m (&b, "", 10.0, M_PI / 2);
  m.apply ();

  std::stringstream s;

  s << b;

  ASSERT_EQ (s.str (), "30,40");
}

TEST (Movement, output)
{
  Blob b {fixed_angle, 20, 40, 5, 100};
  Movement m (&b, "hello", 10.0, M_PI / 2);

  std::stringstream s;

  s << m;

  ASSERT_EQ (s.str (), "hello,10,90");
}

TEST (Rnd, independent)
{
	Blob b1 {Rnd (1, 40), 0, 0, 10, 10};
	Blob b2 {Rnd (1, 40), 0, 0, 10, 10};
	Blob b3 {Rnd (2, 40), 0, 0, 10, 10};
	
	b1.chooseNextAction (std::vector<Blob> {}).apply ();
	b2.chooseNextAction (std::vector<Blob> {}).apply ();
	b3.chooseNextAction (std::vector<Blob> {}).apply ();

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
