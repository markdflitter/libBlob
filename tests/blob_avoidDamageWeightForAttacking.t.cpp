#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, avoidDamageWeightForAttacking_peer)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b1), 0.0);
}

TEST (Blob, avoidDamageWeightForAttacking_positive)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b2), 1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForAttacking_negative)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b2), -1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForAttackingIncreasesForWeakerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 125U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 150U);

	EXPECT_GT (b1.avoidDamageWeightForAttacking (b2), b1.avoidDamageWeightForAttacking (b3));
}

TEST (Blob, avoidDamageWeightForAttackingDecreasesForStrongerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_LT (b1.avoidDamageWeightForAttacking (b2), b1.avoidDamageWeightForAttacking (b3));
}

TEST (Blob, avoidDamageWeightForAttackingDecreasesForWeakerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);

	EXPECT_LT (b2.avoidDamageWeightForAttacking (b1), b3.avoidDamageWeightForAttacking (b1));
}

TEST (Blob, avoidDamageWeightForAttackingIncreasesForStrongerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_GT (b1.avoidDamageWeightForAttacking (b3), b2.avoidDamageWeightForAttacking (b3));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

