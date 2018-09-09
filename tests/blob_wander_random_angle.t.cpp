#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, seeded_normal_distribution_in_degrees)
{
	std::mt19937 gen {0};
	std::normal_distribution<double> dist{0.0, 40.0};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (dist (gen) );
	};

	EXPECT_DOUBLE_EQ (rnd_angle (0.0), 44.911797631556773);
	EXPECT_DOUBLE_EQ (rnd_angle (0.0), 12.112208948296557);
	EXPECT_DOUBLE_EQ (rnd_angle (0.0), 2.8343695072884749);
	EXPECT_DOUBLE_EQ (rnd_angle (0.0), 2.9216560821516016);
	EXPECT_DOUBLE_EQ (rnd_angle (0.0), -56.893033673736078);
	EXPECT_DOUBLE_EQ (rnd_angle (0.0), 60.802779964348865);
}

TEST (Blob, seeded_normal_distribution_in_degrees_progresses)
{
	std::mt19937 gen {0};
	std::normal_distribution<double> dist{0.0, 40.0};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + dist (gen);
	};

	EXPECT_DOUBLE_EQ (rnd_angle (0.0), 44.911797631556773);
	EXPECT_DOUBLE_EQ (rnd_angle (44.911797631556773), 44.911797631556773 + 12.112208948296557);
	EXPECT_DOUBLE_EQ (rnd_angle (44.911797631556773 + 12.112208948296557),
		 44.911797631556773 + 12.112208948296557 + 2.8343695072884749);
	EXPECT_DOUBLE_EQ (rnd_angle (44.911797631556773 + 12.112208948296557 + 2.8343695072884749),
		44.911797631556773 + 12.112208948296557 + 2.8343695072884749 + 2.9216560821516016); 
	EXPECT_DOUBLE_EQ (rnd_angle (44.911797631556773 + 12.112208948296557 + 2.8343695072884749 + 2.9216560821516016),
		44.911797631556773 + 12.112208948296557 + 2.8343695072884749 + 2.9216560821516016 - 56.893033673736078); 
	EXPECT_DOUBLE_EQ (
	     	rnd_angle (44.911797631556773 + 12.112208948296557 + 2.8343695072884749 + 2.9216560821516016 
			   - 56.893033673736078),
         	44.911797631556773 + 12.112208948296557 + 2.8343695072884749 + 2.9216560821516016 - 56.893033673736078 		   	       + 60.802779964348865);
}

TEST (Blob, seeded_normal_distribution_in_radiansi_progresses)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0.0, 40.0};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (2.0 * M_PI * dist (gen) / 360.0);
	};

        EXPECT_DOUBLE_EQ (rnd_angle (0.0), 0.78385874166005687);
        EXPECT_DOUBLE_EQ (rnd_angle (0.0), 0.21139792583729455);
        EXPECT_DOUBLE_EQ (rnd_angle (0.0), 0.0494690801203133);
        EXPECT_DOUBLE_EQ (rnd_angle (0.0), 0.050992518244463381);
        EXPECT_DOUBLE_EQ (rnd_angle (0.0), -0.99297075905469978);
	EXPECT_DOUBLE_EQ (rnd_angle (0.0), 1.0612087047435281);
	EXPECT_DOUBLE_EQ (rnd_angle (0.0), -0.20343135772250606);
}

TEST (Blob, chooses_to_wander_randomly)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0.0, 40.0};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (2.0 * M_PI * dist (gen) / 360.0);
	};

	Blob b ("", rnd_angle, 10.1, 20.2, 5.0);
	EXPECT_DOUBLE_EQ (b.x (), 10.1);
	EXPECT_DOUBLE_EQ (b.y (), 20.2);

	std::vector<Blob> blobs;
	std::shared_ptr<Action> a = b.chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_DOUBLE_EQ (m->_angleInRadians, 0.78385874166005687);
}

TEST (Blob, wanders_randomly)
{
	std::mt19937 gen {0};
	std::normal_distribution<> dist{0.0, 40.0};

	auto rnd_angle = [gen, dist](double previousMoveDirection) mutable 
	{
		return previousMoveDirection + (2.0 * M_PI * dist (gen) / 360.0);
	};

	Blob b ("", rnd_angle, 10.1, 20.2, 5.0, 5.0);
	EXPECT_DOUBLE_EQ (b.x (), 10.1);
	EXPECT_DOUBLE_EQ (b.y (), 20.2);

	std::vector<Blob> blobs;
	std::shared_ptr<Action> m = b.chooseNextAction (blobs);
	m->apply ();
	EXPECT_DOUBLE_EQ (b.x (), 13.630087041046963);
	EXPECT_DOUBLE_EQ (b.y (), 23.74097239224373);

	m = b.chooseNextAction (blobs);
	m->apply ();
	EXPECT_DOUBLE_EQ (b.x (), 17.824580514716409);
	EXPECT_DOUBLE_EQ (b.y (), 26.46241033923874);
	
	m = b.chooseNextAction (blobs);
	m->apply ();
	EXPECT_DOUBLE_EQ (b.x (), 22.14851480285758);
	EXPECT_DOUBLE_EQ (b.y (), 28.9731059145399569);
}

TEST (Blob, different_blobs_wander_independently)
{
	Blob b1 ("", Rnd (1.0, 40.0), 0.0, 0.0, 10.0, 10.0);
	Blob b2 ("", Rnd (1.0, 40.0), 0.0, 0.0, 10.0, 10.0);
	Blob b3 ("", Rnd (2.0, 40.0), 0.0, 0.0, 10.0, 10.0);
	
	std::vector<Blob> blobs;
	b1.chooseNextAction (blobs)->apply ();
	b2.chooseNextAction (blobs)->apply ();
	b3.chooseNextAction (blobs)->apply ();

	EXPECT_DOUBLE_EQ (b1.x (), b2.x ());
	EXPECT_DOUBLE_EQ (b1.y (), b2.y ());
	EXPECT_NE (b1.x (), b3.x ());
	EXPECT_NE (b1.y (), b3.y ());
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

