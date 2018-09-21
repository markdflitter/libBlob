#include <gtest/gtest.h>
#include <blob.h>

//double avoidDamageWeightForAttacking (const Blob& b)
//{
//	return relativeDifference (hitPoints (), b.damage ()) * 2.0;
//}

TEST (test_10_03_blob_avoidDamageWeightForAttacking_t, peer)
{
	Blob b1 = CreateBlob ().HP (100U).damage (100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeightForAttacking (b1), 0.0);
}

TEST (test_10_03_blob_avoidDamageWeightForAttacking_t, positive)
{
	Blob attacker = CreateBlob ().HP (100U);
	Blob target = CreateBlob ().damage (50U);
	
	EXPECT_DOUBLE_EQ (attacker.avoidDamageWeightForAttacking (target), 1.0 / 3.0);
}

TEST (test_10_03_blob_avoidDamageWeightForAttacking_t, negative)
{
	Blob attacker = CreateBlob ().HP (50U);
	Blob target = CreateBlob ().damage (100U);
	
	EXPECT_DOUBLE_EQ (attacker.avoidDamageWeightForAttacking (target), -1.0 / 3.0);
}

TEST (test_10_03_blob_avoidDamageWeightForAttacking_t, increasesForStrongerAttackers)
{
	Blob target = CreateBlob ().damage (100U);
	Blob weakAttacker = CreateBlob ().HP (50U);
	Blob strongAttacker = CreateBlob ().HP (100U);
	
	EXPECT_GT (strongAttacker.avoidDamageWeightForAttacking (target), 
		   weakAttacker.avoidDamageWeightForAttacking (target));
}

TEST (test_10_03_blob_avoidDamageWeightForAttacking_t, increasesForWeakerDefenders)
{
	Blob weakTarget = CreateBlob ().damage (50U);
	Blob strongTarget = CreateBlob ().damage (100U);
	Blob attacker = CreateBlob ().HP (100U);
	
	EXPECT_GT (attacker.avoidDamageWeightForAttacking (weakTarget),
		   attacker.avoidDamageWeightForAttacking (strongTarget));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

