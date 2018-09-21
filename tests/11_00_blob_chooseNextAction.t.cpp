#include <gtest/gtest.h>
#include <blob.h>

TEST (test_11_00_blob_chooseNextAction_t, attackWeight)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).smell (50.0).damage (110U);
	Blob defender = CreateBlob ().position (make_pt (9.0, 12.0)).HP (100U);

	EXPECT_DOUBLE_EQ (attacker.attackWeight (defender), 0.8 * 1.0 / 21.0);
}

TEST (test_11_00_blob_chooseNextAction_t, fleeWeight)
{
	Blob attacker = CreateBlob ().position (make_pt (9.0, 12.0)).damage (110U);
	Blob defender = CreateBlob ().position  (make_pt (3.0, 4.0)).smell (50.0).HP (100U);

	EXPECT_DOUBLE_EQ (defender.fleeWeight (attacker), 0.8 * 1.0 / 21.0);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

