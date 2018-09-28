#include <gtest/gtest.h>
#include <blob.h>
// this tests that we return the right option, just check the test names

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  returns_no_possibilities_with_no_other_blobs)
{
  	Blob b = CreateBlob ();
	std::vector<Blob> blobs;
	auto actions = b.findPossibleActions (blobs);
	
	EXPECT_TRUE (actions.empty ());
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  does_not_consider_self)
{
	std::vector<Blob> blobs {CreateBlob ().smell (100.0)};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_TRUE (actions.empty ());
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  does_not_consider_dead_blobs)
{
	std::vector<Blob> blobs {CreateBlob ().smell (100.0), CreateBlob ()};
	blobs[1].kill ();
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_TRUE (actions.empty ());
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  does_not_consider_blobs_outside_smell_or_in_other_squares)
{
	std::vector<Blob> blobs {CreateBlob ().smell (100.0), CreateBlob ().position (make_pt (100.0, 100.0))};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_TRUE (actions.empty ());
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  adds_flee_and_attack_actions_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob (), CreateBlob ()};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_EQ (actions.size (), 2U);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[1]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
}


TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  adds_flee_and_attack_options_if_can_smell)
{
	std::vector<Blob> blobs {CreateBlob ().smell (5.0), CreateBlob ().position (make_pt (3.0, 4.0))};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_EQ (actions.size (), 2U);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[1]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  adds_flee_and_attack_options_for_more_than_1_blob_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob (), CreateBlob (), CreateBlob ()};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_EQ (actions.size (), 4U);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[1]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[2]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  adds_flee_and_attack_options_for_more_than_1_blob_in_smell_range)
{
	std::vector<Blob> blobs {CreateBlob ().smell (5.0),
			         CreateBlob ().position (make_pt (1.0, 1.0)),
				 CreateBlob ().position (make_pt (2.0, 2.0))};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_EQ (actions.size (), 4U);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[1]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[2]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  adds_flee_and_attack_options_all_relevant_blobs)
{
	std::vector<Blob> blobs {CreateBlob ().smell (5.0),
				 CreateBlob (),
				 CreateBlob (),
			         CreateBlob ().position (make_pt (1.0, 1.0)),
				 CreateBlob ().position (make_pt (2.0, 2.0))};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	EXPECT_EQ (actions.size (), 8U);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[1]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[2]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
	EXPECT_EQ (actions[4].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[4].target, &blobs[3]);
	EXPECT_EQ (actions[5].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[5].target, &blobs[3]);
	EXPECT_EQ (actions[6].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[6].target, &blobs[4]);
	EXPECT_EQ (actions[7].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[7].target, &blobs[4]);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

