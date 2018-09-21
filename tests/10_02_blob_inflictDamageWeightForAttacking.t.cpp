#include <gtest/gtest.h>
#include <blob.h>

//double inflictDamageWeightForAttacking (const Blob& b)
//{
//	return relativeDifference (damage (), b.hitPoints ()) * 2.0;
//}

TEST (Blob, avoidDamageWeightForAttacking_peer)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b1), 0.0);
}


TEST (Blob, inflictDamageWeightForAttacking_positive)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0.0, 0U, [](double a) {return a;}, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeightForAttacking (b2), 10.0 / 210.0);	
}

TEST (Blob, inflictDamageWeightForAttacking_negative)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0.0, 0U, [](double a) {return a;}, 90U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeightForAttacking (b2), -10.0 / 190.0);
}

TEST (Blob, inflictDamageWeightForAttacking_increasesForStrongerAttackers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 500U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);

	EXPECT_GT (b3.inflictDamageWeightForAttacking (b1), b2.inflictDamageWeightForAttacking (b1));
}

TEST (Blob, inflictDamageWeightForAttacking_increasesForWeakerDefenders)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0U, 0.0, [](double a) {return a;}, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 50U);
	Blob b3 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_GT (b1.inflictDamageWeightForAttacking (b2), b2.inflictDamageWeightForAttacking (b3));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

