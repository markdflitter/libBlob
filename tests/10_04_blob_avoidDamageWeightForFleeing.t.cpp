#include <gtest/gtest.h>
#include <blob.h>

//double avoidDamageWeightForFleeing (const Blob& b)
//{
//	return relativeDifference (b.damage (), hitPoints ()) * 2.0;
//}

TEST (test_10_04_blob_avoidDamageWeightForFleeing_t, peer)
{
	Blob b1 = CreateBlob ().HP (100U).damage (100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForFleeing (b1), 0.0);
}

TEST (test_10_04_blob_avoidDamageWeightForFleeing_t, positive)
{
	Blob Attacker = CreateBlob ().damage (100U);
	Blob runner = CreateBlob ().HP (50U);

	EXPECT_DOUBLE_EQ (runner.avoidDamageWeightForFleeing (Attacker), 1.0 / 3.0);
}

TEST (test_10_04_blob_avoidDamageWeightForFleeing_t, negative)
{
	Blob Attacker = CreateBlob ().damage (50U);
	Blob runner = CreateBlob ().HP (100U);

	EXPECT_DOUBLE_EQ (runner.avoidDamageWeightForFleeing (Attacker), -1.0 / 3.0);
}

TEST (test_10_04_blob_avoidDamageWeightForFleeing_t, increasesForStrongerAttackers)
{
	Blob runner = CreateBlob ().HP (100U);
	Blob weakAttacker  = CreateBlob ().damage (50U);
	Blob strongAttacker  = CreateBlob ().damage (100U);

	EXPECT_GT (runner.avoidDamageWeightForFleeing (strongAttacker),
		   runner.avoidDamageWeightForFleeing (weakAttacker));
}

TEST (test_10_04_blob_avoidDamageWeightForFleeing_t, increasesForWeakerDefenders)
{
	Blob weakRunner = CreateBlob ().HP (50U);
	Blob strongRunner  = CreateBlob ().HP (100U);
	Blob attacker  = CreateBlob ().damage (100U);

	EXPECT_GT (weakRunner.avoidDamageWeightForFleeing (attacker),
		   strongRunner.avoidDamageWeightForFleeing (attacker));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

