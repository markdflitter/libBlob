#include <gtest/gtest.h>
#include <blob.h>

TEST (test_10_03_blob_fleeWeight_t, avoidDamageWeight_peer)
{
	Blob b1 = CreateBlob ().HP (100U).damage (100U);

	EXPECT_DOUBLE_EQ (b1.avoidDamageWeight (b1), 0.0);
}

TEST (test_10_03_blob_fleeWeight_t, avoidDamageWeight_positive)
{
	Blob Attacker = CreateBlob ().damage (100U);
	Blob runner = CreateBlob ().HP (50U);

	EXPECT_DOUBLE_EQ (runner.avoidDamageWeight (Attacker), 1.0 / 3.0);
}

TEST (test_10_03_blob_fleeWeight_t, avoidDamageWeight_negative)
{
	Blob Attacker = CreateBlob ().damage (50U);
	Blob runner = CreateBlob ().HP (100U);

	EXPECT_DOUBLE_EQ (runner.avoidDamageWeight (Attacker), -1.0 / 3.0);
}

TEST (test_10_03_blob_fleeWeight_t, avoidDamageWeight_increases_for_stronger_attackers)
{
	Blob runner = CreateBlob ().HP (100U);
	Blob weakAttacker  = CreateBlob ().damage (50U);
	Blob strongAttacker  = CreateBlob ().damage (100U);

	EXPECT_GT (runner.avoidDamageWeight (strongAttacker),
		   runner.avoidDamageWeight (weakAttacker));
}

TEST (test_10_03_blob_fleeWeight_t, avoidDamageWeight_increases_for_weaker_defenders)
{
	Blob weakRunner = CreateBlob ().HP (50U);
	Blob strongRunner  = CreateBlob ().HP (100U);
	Blob attacker  = CreateBlob ().damage (100U);

	EXPECT_GT (weakRunner.avoidDamageWeight (attacker),
		   strongRunner.avoidDamageWeight (attacker));
}

TEST (test_10_03_blob_fleeWeight_t, fleeWeight)
{
	Blob attacker = CreateBlob ().position (make_pt (9.0, 12.0)).damage (110U);
	Blob defender = CreateBlob ().position  (make_pt (3.0, 4.0)).smell (50.0).HP (100U);

	EXPECT_DOUBLE_EQ (defender.fleeWeight (attacker), 0.8 * 1.0 / 21.0);
}

TEST (test_10_03_blob_fleeWeight_t, fleeWeight_scales_with_distance)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).damage (100U);
	Blob defender1 = CreateBlob ().position (make_pt (10.0, 20.0)).smell (100.0).HP (50U);
	Blob defender2 = CreateBlob ().position (make_pt (20.0, 40.0)).smell (100.0).HP (50U);

	EXPECT_GT (defender1.fleeWeight (attacker), defender2.fleeWeight (attacker));
}

TEST (test_10_03_blob_fleeWeight_t, distance_does_not_affect_fleeWeight_in_same_square)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).damage (100U);
	Blob defender1 = CreateBlob ().position (make_pt (3.1, 4.0)).smell (100.0).HP (50U);
	Blob defender2 = CreateBlob ().position (make_pt (3.9, 4.0)).smell (100.0).HP (50U);

	EXPECT_DOUBLE_EQ (defender1.fleeWeight (attacker), defender2.fleeWeight (attacker));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

