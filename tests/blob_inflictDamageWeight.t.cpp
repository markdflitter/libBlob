#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, inflictDamageWeight_peers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeight (b1), 0.0);
}

TEST (Blob, inflictDamageWeight_stronger)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeight (b2), 1.0 / 3.0);
}

TEST (Blob, inflictDamageWeight_weaker)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeight (b2), -1.0 / 3.0);
}

TEST (Blob, inflictDamageWeightIncreasesForWeakerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_GT (b1.inflictDamageWeight (b3), b1.inflictDamageWeight (b2));
}

TEST (Blob, inflictDamageWeightDecreasesForStrongerTargets)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 125U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 150U);

	EXPECT_LT (b1.inflictDamageWeight (b3), b1.inflictDamageWeight (b2));
}

TEST (Blob, inflictDamageWeightDecreasesForWeakerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);

	EXPECT_LT (b2.inflictDamageWeight (b1), b3.inflictDamageWeight (b1));
}

TEST (Blob, inflictDamageWeightIncreasesForStrongerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 25U);

	EXPECT_GT (b1.inflictDamageWeight (b3), b2.inflictDamageWeight (b3));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

