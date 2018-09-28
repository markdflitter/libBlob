#include <gtest/gtest.h>
#include <blob.h>
/*
std::vector<ActionPossibility> findPossibleActions (std::vector<Blob>& others)
{	
	std::vector <ActionPossibility> possibilities;

	for (auto& b : others)
	{
		if ((&b != this) && !b.isDead ())
		{
			double a = _aggressionFn (_aggression);

			if (isInSameSquare (b) || canSmell (b))
			{
				possibilities.push_back (
					ActionPossibility {ActionPossibility::attack, attackWeight (b) + a, &b});
				possibilities.push_back (
					ActionPossibility {ActionPossibility::flee, fleeWeight (b) - a, &b});
			}
		}
	}
		
	return possibilities;
}
*/

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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

TEST (test_11_01_blob_chooseNextAction_findPossibleActions_t,
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

