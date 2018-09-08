#include <gtest/gtest.h>
#include <blob.h>

constexpr double threshold = 0.00001;

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

