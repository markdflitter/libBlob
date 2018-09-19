#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, inflictDamageWeightForAttacking_inflictDamageWeightHigher)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeightForAttacking (b2), 10.0 / 210.0);	
}

TEST (Blob, inflictDamageWeightForAttacking_avoidDamageWeightHigher)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeightForAttacking (b2), 10.0 / 210.0);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

