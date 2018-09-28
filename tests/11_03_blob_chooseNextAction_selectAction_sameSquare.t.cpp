#include <gtest/gtest.h>
#include <blob.h>

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  distance_does_not_affect_weight_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions = blobs[0].findPossibleActions (blobs);
	
	for (auto action : actions)
	{
		if (action.action == Blob::ActionPossibility::attack)
		{
			EXPECT_DOUBLE_EQ (action.weight, 5.0 / 6.0);
		}
		else
		{
			EXPECT_DOUBLE_EQ (action.weight, -1.0 / 6.0);
		}
	}
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_flee_stronger_attacker_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (50U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (50U).damage (500U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions = blobs[0].findPossibleActions (blobs);

	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_EQ (actions[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[3].target, &blobs[2]);
	EXPECT_GT (actions[3].weight, actions[1].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  weaker_defender_more_likely_to_flee_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (25U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (50U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions_blob0 = blobs[0].findPossibleActions (blobs);
	auto actions_blob1 = blobs[1].findPossibleActions (blobs);

	EXPECT_EQ (actions_blob0[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions_blob0[3].target, &blobs[2]);
	EXPECT_EQ (actions_blob1[3].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions_blob1[3].target, &blobs[2]);
	EXPECT_GT (actions_blob0[3].weight, actions_blob1[1].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  stronger_attacker_with_more_damage_more_likely_to_attack_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (50U).damage (200U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (50U).damage (200U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions_blob0 = blobs[0].findPossibleActions (blobs);
	auto actions_blob1 = blobs[1].findPossibleActions (blobs);

	EXPECT_EQ (actions_blob0[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob0[2].target, &blobs[2]);
	EXPECT_EQ (actions_blob1[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob1[2].target, &blobs[2]);
	EXPECT_GT (actions_blob1[2].weight, actions_blob0[2].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  stronger_attacker_with_moreHP_more_likely_to_attack_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (50U).damage (0U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (100U).damage (0U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (100U).damage (100U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions_blob0 = blobs[0].findPossibleActions (blobs);
	auto actions_blob1 = blobs[1].findPossibleActions (blobs);

	EXPECT_EQ (actions_blob0[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob0[2].target, &blobs[2]);
	EXPECT_EQ (actions_blob1[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob1[2].target, &blobs[2]);
	EXPECT_GT (actions_blob1[2].weight, actions_blob0[2].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_attack_weaker_defender_with_lowerHP_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (25U).damage (100U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[1]);
	EXPECT_GT (actions[0].weight, actions[2].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  more_likely_to_attack_weaker_defender_with_lower_damage_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (100U).damage (25U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (100U).damage (50U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (50U).damage (100U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[2].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[2].target, &blobs[1]);
	EXPECT_GT (actions[0].weight, actions[2].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  weak_defender_more_likely_to_flee_than_attack_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (20U).damage (25U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (100U).damage (100U).position (make_pt (5.9, 5.9))};
	auto actions = blobs[0].findPossibleActions (blobs);

	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[1]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[1]);
	EXPECT_GT (actions[1].weight, actions[0].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  stronger_attacker_with_more_damage_more_likely_to_attack_than_flee_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (10U).damage (100U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (100U).damage (100U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions = blobs[1].findPossibleActions (blobs);

	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[0]);
	EXPECT_GT (actions[0].weight, actions[1].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  stronger_attacker_with_more_HP_more_likely_to_attack_than_flee_if_in_same_square)
{
	std::vector<Blob> blobs {CreateBlob ().HP (10U).damage (100U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (200U).damage (10U).aggression (0.5).position (make_pt (5.9, 5.9))};
	auto actions = blobs[1].findPossibleActions (blobs);

	EXPECT_EQ (actions[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions[0].target, &blobs[0]);
	EXPECT_EQ (actions[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions[1].target, &blobs[0]);
	EXPECT_GT (actions[0].weight, actions[1].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  more_aggressive_in_same_square_is_more_likely_to_attack)
{
	std::vector<Blob> blobs {CreateBlob ().HP (25U).damage (25U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (100U).damage (100U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (100U).damage (100U).aggression (0.6).position (make_pt (5.9, 5.9))};
	auto actions_blob1 = blobs[1].findPossibleActions (blobs);
	auto actions_blob2 = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions_blob1[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob1[0].target, &blobs[0]);
	EXPECT_EQ (actions_blob2[0].action, Blob::ActionPossibility::attack);
	EXPECT_EQ (actions_blob2[0].target, &blobs[0]);
	EXPECT_GT (actions_blob2[0].weight, actions_blob1[0].weight);
}

TEST (test_11_03_blob_chooseNextAction_findPossibleActions_t,
  more_aggressive_in_same_square_is_less_likely_to_flee)
{
	std::vector<Blob> blobs {CreateBlob ().HP (1000U).damage (1000U).aggression (0.5).position (make_pt (5.0, 5.0)),
				 CreateBlob ().HP (100U).damage (100U).aggression (0.5).position (make_pt (5.1, 5.1)),
				 CreateBlob ().HP (100U).damage (100U).aggression (0.6).position (make_pt (5.9, 5.9))};
	auto actions_blob1 = blobs[1].findPossibleActions (blobs);
	auto actions_blob2 = blobs[2].findPossibleActions (blobs);

	EXPECT_EQ (actions_blob1[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions_blob1[1].target, &blobs[0]);
	EXPECT_EQ (actions_blob2[1].action, Blob::ActionPossibility::flee);
	EXPECT_EQ (actions_blob2[1].target, &blobs[0]);
	EXPECT_LT (actions_blob2[1].weight, actions_blob1[1].weight);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

