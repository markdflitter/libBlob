#include <gtest/gtest.h>
#include <blob.h>

//double avoidDamageWeightForFleeing (const Blob& b)
//{
//	return relativeDifference (b.damage (), hitPoints ()) * 2.0;
//}

TEST (Blob, avoidDamageWeightForFleeing_peer)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForFleeing (b1), 0.0);
}

TEST (Blob, avoidDamageWeightForFleeing_positive)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForFleeing (b2), 1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForFleeing_negative)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 50U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForFleeing (b2), -1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForFleeing_increasesForStrongerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 500U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);

	EXPECT_GT (b1.avoidDamageWeightForFleeing (b3), b1.avoidDamageWeightForFleeing (b2));
}

TEST (Blob, avoidDamageWeightForFleeing_increasesForWeakerDefenders)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_GT (b2.avoidDamageWeightForFleeing (b1), b3.avoidDamageWeightForFleeing (b1));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

