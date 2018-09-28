#include <gtest/gtest.h>
#include <blob.h>

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_attack_closer_blobs_in_smell_range)
{
	std::vector<Blob> blobs {CreateBlob ().HP (50U).damage (80U).smell(100).aggression (0.5).position (make_pt (3.0, 4.0)),
				 CreateBlob ().HP (50U).damage (80U).aggression (0.5).position (make_pt (10.0, 20.0)),
				 CreateBlob ().HP (50U).damage (80U).aggression (0.5).position (make_pt (20.0, 30.0))};
	auto actions = blobs[0].findPossibleActions (blobs);

	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[1]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[2]);
	EXPECT_GT (actions[0].weight, actions[2].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_flee_closer_blobs_in_smell_range)
{
	std::vector<Blob> blobs {CreateBlob ().HP (50U).damage (80U).smell(100).aggression (0.5).position (make_pt (3.0, 4.0)),
				 CreateBlob ().HP (50U).damage (80U).aggression (0.5).position (make_pt (10.0, 20.0)),
				 CreateBlob ().HP (50U).damage (80U).aggression (0.5).position (make_pt (20.0, 30.0))};
	auto actions = blobs[0].findPossibleActions (blobs);

	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
	EXPECT_GT (actions[1].weight, actions[3].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_flee_stronger_attacker_in_smell_range)
{
	std::vector<Blob> blobs {CreateBlob ().HP (50U).damage (80U).smell(100).aggression (0.5).position (make_pt (3.0, 4.0)),
				 CreateBlob ().HP (50U).damage (80U).aggression (0.5).position (make_pt (10.0, 20.0)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (10.0, 20.0))};
	auto actions = blobs[0].findPossibleActions (blobs);

	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
	EXPECT_GT (actions[3].weight, actions[1].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  weaker_defender_more_likely_to_flee_blob_in_smell_range)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (20U).damage (80U).smell(100.0).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).smell (100.0).aggression (0.5).position (make_pt (10.0, 20.0)),
		CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (10.0, 20.0))};
	auto actions_blob0 = blobs[0].findPossibleActions (blobs);
	auto actions_blob1 = blobs[1].findPossibleActions (blobs);

	EXPECT_EQ (actions_blob0.size (), 4);
	EXPECT_EQ (actions_blob1.size (), 4);
	EXPECT_EQ (actions_blob0[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions_blob0[3].target, &blobs[2]);
	EXPECT_EQ (actions_blob1[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions_blob1[3].target, &blobs[2]);
	EXPECT_GT (actions_blob0[3].weight, actions_blob1[1].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  will_flee_close_weaker_blob_in_smell_range_even_if_there_is_stronger_one_further_away)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (20U).damage (80U).smell (500.0).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).smell (100.0).aggression (0.5).position (make_pt (10.0, 20.0)),
		CreateBlob ().HP (50U).damage (1000U).aggression (0.5).position (make_pt (200.0, 200.0))};
	auto actions = blobs[0].findPossibleActions (blobs);

	EXPECT_EQ (actions.size (), 4);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
	EXPECT_GT (actions[1].weight, actions[3].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  will_flee_stronger_blob_in_smell_range_even_if_there_is_weaker_one_closer)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (20U).damage (80U).smell (500.0).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).smell (100.0).aggression (0.5).position (make_pt (10.0, 20.0)),
		CreateBlob ().HP (50U).damage (1000U).aggression (0.5).position (make_pt (100.0, 100.0))};
	auto actions = blobs[0].findPossibleActions (blobs);

	EXPECT_EQ (actions.size (), 4);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
	EXPECT_GT (actions[3].weight, actions[1].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_attack_weaker_blob_in_smell_range_less_HP)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (20U).damage (80U).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (1000U).smell (100.0).aggression (0.5).position (make_pt (10.0, 12.0))};
	auto actions = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions.size (), 4);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[1]);
	EXPECT_GT (actions[0].weight, actions[2].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_attack_weaker_blob_in_smell_range_more_damage)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (20U).damage (80U).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).smell (100.0).aggression (0.5).position (make_pt (10.0, 12.0)),
		CreateBlob ().HP (50U).damage (1000U).smell (100.0).aggression (0.5).position (make_pt (10.0, 12.0))};
	auto actions_blob1 = blobs[1].findPossibleActions (blobs);
	auto actions_blob2 = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions_blob1.size (), 4);
	EXPECT_EQ (actions_blob2.size (), 4);
	EXPECT_EQ (actions_blob1[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob1[0].target, &blobs[0]);
	EXPECT_EQ (actions_blob2[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob2[0].target, &blobs[0]);
	EXPECT_GT (actions_blob2[0].weight, actions_blob1[0].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_attack_closer_blob_in_smell_range)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (50U).damage (80U).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).smell (100.0).aggression (0.5).position (make_pt (5.0, 6.0)),
		CreateBlob ().HP (50U).damage (1000U).smell (100.0).aggression (0.5).position (make_pt (10.0, 12.0))};
	auto actions = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions.size (), 4);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[1]);
	EXPECT_GT (actions[2].weight, actions[0].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_attack_closer_blob_in_smell_range_even_if_there_is_a_weaker_one_further_away)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (40U).damage (80U).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).smell (100.0).aggression (0.5).position (make_pt (5.0, 6.0)),
		CreateBlob ().HP (50U).damage (1000U).smell (100.0).aggression (0.5).position (make_pt (10.0, 12.0))};
	auto actions = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions.size (), 4);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[1]);
	EXPECT_GT (actions[2].weight, actions[0].weight);
}

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
  will_attack_distant_blob_in_smell_range_if_there_it_is_weak_enough)
{
	std::vector<Blob> blobs {
		CreateBlob ().HP (1U).damage (80U).aggression (0.5).position (make_pt (3.0, 4.0)),
		CreateBlob ().HP (50U).damage (80U).smell (100.0).aggression (0.5).position (make_pt (5.0, 6.0)),
		CreateBlob ().HP (50U).damage (1000U).smell (100.0).aggression (0.5).position (make_pt (10.0, 12.0))};
	auto actions = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions.size (), 4);
	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[1]);
	EXPECT_GT (actions[0].weight, actions[2].weight);
}

// blobs in smell range
// attack action
  // weaker blobs more likely to flee	
  //stronger blobs more likely to attack
  // more aggressive blobs more likely to attack
  // less aggressive blobs more likely to flee
    

// STILL NEEDS THOUGHT
// combined
//  more likely to flee blobs in same square
// may flee blobs further away
//aggression randomness

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

