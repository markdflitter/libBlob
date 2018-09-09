#include <gtest/gtest.h>
#include <blob.h>

double fixed_angle (double previousMoveDirection)
{
	return previousMoveDirection + M_PI / 4.0;
};


TEST (fixed_angle, is_fixed)
{
	for (int i = 0; i < 8; i++)
	{
		EXPECT_DOUBLE_EQ (fixed_angle (i * M_PI / 4.0), (i * M_PI / 4.0) + M_PI / 4.0);
	}
}

TEST (Blob, uses_fixed_angle)
{
	Blob b ("", fixed_angle, 10.1, 20.2, 5.0, 5.0);

	for (size_t step = 1; step <= 8; step++)
	{
		std::shared_ptr<Action> a = b.createActionWander ();
		ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
		std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
		EXPECT_EQ (m->_reason, "wandering");
		EXPECT_DOUBLE_EQ (m->_speed, 5.0);
		EXPECT_DOUBLE_EQ (m->_angleInRadians, step * (M_PI / 4.0));
		m->apply ();
	}
}

TEST (Blob, wanders_in_a_circle)
{
	Blob b ("", fixed_angle, 10.1, 20.2, 5.0, 5.0);

	std::shared_ptr<Action> a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&b, "wandering", 5, M_PI / 4));
	a->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 13.635533905932737);
	EXPECT_DOUBLE_EQ (b.y (), 23.735533905932737);

	a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
       	EXPECT_TRUE (*m  == Movement (&b, "wandering", 5, M_PI / 2));
	a->apply ();
	EXPECT_DOUBLE_EQ (b.x (), 18.635533905932739);
	EXPECT_DOUBLE_EQ (b.y (), 23.735533905932737);

	a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (*m  == Movement (&b, "wandering", 5, 3 * M_PI / 4));
	a->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 22.171067811865477);
	EXPECT_DOUBLE_EQ (b.y (), 20.2);

	a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (*m  == Movement (&b, "wandering", 5, M_PI));
	a->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 22.171067811865477);
	EXPECT_DOUBLE_EQ (b.y (), 15.2);

	a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (*m  == Movement (&b, "wandering", 5, 5 * M_PI / 4));
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 18.635533905932739);
	EXPECT_DOUBLE_EQ (b.y (), 11.664466094067262);

	a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (*m  == Movement (&b, "wandering", 5, 3 * M_PI / 2));
	a->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 13.635533905932739);
	EXPECT_DOUBLE_EQ (b.y (), 11.664466094067262);
	
	a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (*m  == Movement (&b, "wandering", 5, 7 * M_PI / 4));
	a->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 10.1);
	EXPECT_DOUBLE_EQ (b.y (), 15.2);

	a = b.createActionWander ();
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (m));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (*m  == Movement (&b, "wandering", 5, 2 * M_PI));
	a->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 10.1);
	EXPECT_DOUBLE_EQ (b.y (), 20.2);
}



TEST (Blob, chooses_to_wander_in_a_circle)
{
	Blob b ("mark", fixed_angle, 10.1, 20.2, 5, 5, 0, 0);
	std::vector<Blob> blobs;
	
	std::shared_ptr<Action> m = b.chooseNextAction (blobs);
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 13.63553390593273000);
	EXPECT_DOUBLE_EQ (b.y (), 23.73553390593272737);

	m = b.chooseNextAction (blobs);
        m->apply ();
	EXPECT_DOUBLE_EQ (b.x (), 18.635533905932739);
	EXPECT_DOUBLE_EQ (b.y (), 23.735533905932737);
	
	m = b.chooseNextAction (blobs);
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 22.171067811865477);
	EXPECT_DOUBLE_EQ (b.y (), 20.2);

	m = b.chooseNextAction (blobs);
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 22.171067811865477);
	EXPECT_DOUBLE_EQ (b.y (), 15.2);

	m = b.chooseNextAction (blobs);
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 18.635533905932739);
	EXPECT_DOUBLE_EQ (b.y (), 11.664466094067262);

	m = b.chooseNextAction (blobs);
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 13.635533905932739);
	EXPECT_DOUBLE_EQ (b.y (), 11.664466094067262);

	m = b.chooseNextAction (blobs);
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 10.1);
	EXPECT_DOUBLE_EQ (b.y (), 15.2);
	
	m = b.chooseNextAction (blobs);
	m->apply ();
        EXPECT_DOUBLE_EQ (b.x (), 10.1);
	EXPECT_DOUBLE_EQ (b.y (), 20.2);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

