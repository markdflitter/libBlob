#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, avoidDamageWeightForFleeing_peer)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForFleeing (b1), 0.0);
}

TEST (Blob, avoidDamageWeightForFleeing_positive)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForFleeing (b2), 1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForFleeing_negative)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForFleeing (b2), -1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForFleeingIncreasesForWeakerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 125U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 150U);

	EXPECT_GT (b1.avoidDamageWeightForFleeing (b3), b2.avoidDamageWeightForFleeing (b3));
}

TEST (Blob, avoidDamageWeightForFleeingDecreasesForStrongerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_LT (b2.avoidDamageWeightForFleeing (b1), b3.avoidDamageWeightForFleeing (b1));
}

TEST (Blob, avoidDamageWeightForFleeingDecreasesForWeakerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);

	EXPECT_LT (b1.avoidDamageWeightForFleeing (b2), b1.avoidDamageWeightForFleeing (b3));
}

TEST (Blob, avoidDamageWeightForFleeingIncreasesForStrongerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_GT (b3.avoidDamageWeightForFleeing (b1), b3.avoidDamageWeightForFleeing (b2));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

