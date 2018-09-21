#include <gtest/gtest.h>
#include <blob.h>

//double inflictDamageWeightForAttacking (const Blob& b)
//{
//	return relativeDifference (damage (), b.hitPoints ()) * 2.0;
//}

TEST (test_10_02_blob_inflictDamageWeightForAttacking, peer)
{
	Blob b1 = CreateBlob ().HP (100U).damage (100U);

	EXPECT_DOUBLE_EQ (b1.inflictDamageWeightForAttacking (b1), 0.0);
}


TEST (test_10_02_blob_inflictDamageWeightForAttacking, positive)
{
	Blob attacker = CreateBlob ().damage (110U);
	Blob target = CreateBlob ().HP (100U);

	EXPECT_DOUBLE_EQ (attacker.inflictDamageWeightForAttacking (target), 10.0 / 210.0);	
}

TEST (test_10_02_blob_inflictDamageWeightForAttacking, negative)
{
	Blob attacker = CreateBlob ().damage (90U);
	Blob target = CreateBlob ().HP (100U);

	EXPECT_DOUBLE_EQ (attacker.inflictDamageWeightForAttacking (target), -10.0 / 190.0);
}

TEST (test_10_02_blob_inflictDamageWeightForAttacking, increasesForStrongerAttackers)
{
	Blob target = CreateBlob ().HP (500U);
	Blob weakAttacker = CreateBlob ().damage (50U);
	Blob strongAttacker = CreateBlob ().damage (100U);

	EXPECT_GT (strongAttacker.inflictDamageWeightForAttacking (target),
		   weakAttacker.inflictDamageWeightForAttacking (target));
}

TEST (test_10_02_blob_inflictDamageWeightForAttacking, increasesForWeakerDefenders)
{
	Blob weakTarget = CreateBlob ().HP (50U);
	Blob strongTarget = CreateBlob ().HP (100U);
	Blob attacker = CreateBlob ().damage (100U);

	EXPECT_GT (attacker.inflictDamageWeightForAttacking (weakTarget),
		   attacker.inflictDamageWeightForAttacking (strongTarget));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

