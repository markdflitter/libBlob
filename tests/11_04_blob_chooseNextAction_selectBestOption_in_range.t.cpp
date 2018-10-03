#include <gtest/gtest.h>
#include <blob.h>

auto weakest = CreateBlob ().HP (25U).smell (100.0).position (make_pt (5.0, 5.0));
auto weaker = CreateBlob ().HP (50U).smell (100.0).position (make_pt (5.0, 5.0));
auto stronger = CreateBlob ().HP (200U).smell (100.0).damage (100U).position (make_pt (10.0, 10.0));
auto strongest = CreateBlob ().HP (200U).smell (100.0).damage (200U).position (make_pt (10.0, 10.0));

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, weaker_flees_stronger)
{
	std::vector <Blob> b {weaker, stronger};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(flee, 0, &b[1])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, weaker_flees_closest_if_same_strength)
{
	std::vector <Blob> b {weaker, stronger, stronger.position (make_pt (7.0, 7.0))};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(flee, 0, &b[2])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, weaker_flees_most_smelly_if_same_strength)
{
	std::vector <Blob> b {weaker, weaker.smell (50.0), stronger};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(flee, 0, &b[2])));
	EXPECT_TRUE (b[1].chooseBestOption (b).matches (Option(flee, 0, &b[2])));
	EXPECT_GT (b[0].chooseBestOption (b).weight (), b[1].chooseBestOption (b).weight ());
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, weaker_flees_strongest_if_equidistant)
{
	std::vector <Blob> b {weaker, stronger, strongest};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(flee, 0, &b[2])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, weakest_flees)
{
	std::vector <Blob> b {weakest, weaker, stronger};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(flee, 0, &b[2])));
	EXPECT_TRUE (b[1].chooseBestOption (b).matches (Option(flee, 0, &b[2])));
	EXPECT_GT (b[0].chooseBestOption (b).weight (), b[1].chooseBestOption (b).weight ());
}
TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, weaker_flees_nearby_weaker)
{
	std::vector <Blob> b {weakest, weaker.damage (26U).position (make_pt (6.5, 6.5)), stronger.position (make_pt (5.0, 102.0))};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(flee, 0, &b[1])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, weaker_flees_distant_stronger)
{
	std::vector <Blob> b {weakest, weaker.damage (26U).position (make_pt (6.5, 6.5)), strongest.position (make_pt (5.0, 102.0))};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(flee, 0, &b[2])));
}

TEST (test_11_03_blob_chooseNextAction_selectBestOption_same_square_t, weaker_wont_flee_if_aggressive)
{
	std::vector <Blob> b {weakest.aggression (1.0), stronger};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(attack, 0, &b[1])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, stronger_attacks_weaker)
{
	std::vector <Blob> b {stronger, weaker};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(attack, 0, &b[1])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, stronger_attacks_closest_if_same_strength)
{
	std::vector <Blob> b {weaker, weaker.position (make_pt (7.0, 7.0)), stronger};
	EXPECT_TRUE (b[2].chooseBestOption (b).matches (Option(attack, 0, &b[1])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, stronger_attacks_most_smelly_if_same_strength)
{
	std::vector <Blob> b {weaker, stronger.smell (50.0), stronger};
	EXPECT_TRUE (b[1].chooseBestOption (b).matches (Option(attack, 0, &b[0])));
	EXPECT_TRUE (b[2].chooseBestOption (b).matches (Option(attack, 0, &b[0])));
	EXPECT_GT (b[2].chooseBestOption (b).weight (), b[1].chooseBestOption (b).weight ());
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, stronger_attacks_weakest_if_equidistant)
{
	std::vector <Blob> b {weakest, weaker, stronger};
	EXPECT_TRUE (b[2].chooseBestOption (b).matches (Option(attack, 0, &b[0])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, strongest_attacks)
{
	std::vector <Blob> b {strongest, stronger, weaker};
	EXPECT_TRUE (b[0].chooseBestOption (b).matches (Option(attack, 0, &b[2])));
	EXPECT_TRUE (b[1].chooseBestOption (b).matches (Option(attack, 0, &b[2])));
	EXPECT_GT (b[0].chooseBestOption (b).weight (), b[1].chooseBestOption (b).weight ());
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, stronger_attacks_nearby_stronger)
{
	std::vector <Blob> b {weakest, stronger.HP (190U).position (make_pt (5.0, 100.0)), strongest.position (make_pt (5.0, 102.0))};
	EXPECT_TRUE (b[2].chooseBestOption (b).matches (Option(attack, 0, &b[1])));
}

TEST (test_11_04_blob_chooseNextAction_selectBestOption_in_range_t, stronger_attacks_distant_weaker)
{
	std::vector <Blob> b {weakest, stronger.HP (199U).position (make_pt (5.0, 100.0)), strongest.position (make_pt (5.0, 102.0))};
	EXPECT_TRUE (b[2].chooseBestOption (b).matches (Option(attack, 0, &b[0])));
}

TEST (test_11_03_blob_chooseNextAction_selectBestOption_same_square_t, stronger_wont_attack_if_cowardly)
{
	std::vector <Blob> b {weakest, stronger.aggression (-1.0)};
	EXPECT_TRUE (b[1].chooseBestOption (b).matches (Option(flee, 0, &b[0])));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

