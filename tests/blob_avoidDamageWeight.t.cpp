#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, avoidDamageWeight_peer)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeight (b1), 0.0);
}

TEST (Blob, avoidDamageWeight_positive)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeight (b2), 1.0 / 3.0);
}

TEST (Blob, avoidDamageWeight_negative)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeight (b2), -1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightIncreasesForWeakerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 125U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 150U);

	EXPECT_GT (b1.avoidDamageWeight (b2), b1.avoidDamageWeight (b3));
}

TEST (Blob, avoidDamageWeightDecreasesForStrongerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_LT (b1.avoidDamageWeight (b2), b1.avoidDamageWeight (b3));
}

TEST (Blob, avoidDamageWeightDecreasesForWeakerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);

	EXPECT_LT (b2.avoidDamageWeight (b1), b3.avoidDamageWeight (b1));
}

TEST (Blob, avoidDamageWeightIncreasesForStrongerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_GT (b1.avoidDamageWeight (b3), b2.avoidDamageWeight (b3));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

