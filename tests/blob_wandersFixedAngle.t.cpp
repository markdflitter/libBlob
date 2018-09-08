#include <gtest/gtest.h>
#include <blob.h>

constexpr double threshold = 0.00001;

double fixed_angle (double previousMoveDirection)
{
	return previousMoveDirection + M_PI / 4;
};


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



int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

