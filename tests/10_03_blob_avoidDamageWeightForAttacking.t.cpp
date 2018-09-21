#include <gtest/gtest.h>
#include <blob.h>

//double avoidDamageWeightForAttacking (const Blob& b)
//{
//	return relativeDifference (hitPoints (), b.damage ()) * 2.0;
//}


TEST (Blob, avoidDamageWeightForAttacking_peer)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b1), 0.0);
}

TEST (Blob, avoidDamageWeightForAttacking_positive)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 50U);
	
	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b2), 1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForAttacking_negative)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);
	
	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b2), -1.0 / 3.0);
}

TEST (Blob, avoidDamageWeightForAttacking_increasesForStrongerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 50U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_GT (b3.avoidDamageWeightForAttacking (b1), b2.avoidDamageWeightForAttacking (b1));
}

TEST (Blob, avoidDamageWeightForAttacking_increasesForWeakerDefenders)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 500U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);

	EXPECT_GT (b1.avoidDamageWeightForAttacking (b2), b2.avoidDamageWeightForAttacking (b3));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

