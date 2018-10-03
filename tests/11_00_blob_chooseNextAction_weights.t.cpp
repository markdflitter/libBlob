#include <gtest/gtest.h>
#include <blob.h>
//rename file

TEST (test_11_00_blob_chooseNextAction_weights_t, attackWeight_usesInflictDamageWeight)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).smell (1.0).HP (100U).damage (100U);
	Blob defender = CreateBlob ().position (make_pt (3.0, 5.0)).HP (0U).damage (100U);

	EXPECT_DOUBLE_EQ (attacker.attackWeight (defender), 1.0);
}

TEST (test_11_00_blob_chooseNextAction_weights_t, attackWeight_scalesWithDistance)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).smell (100.0).damage (100U);
	Blob defender1 = CreateBlob ().position (make_pt (10.0, 20.0)).HP (50U);
	Blob defender2 = CreateBlob ().position (make_pt (20.0, 40.0)).HP (50U);

	EXPECT_GT (attacker.attackWeight (defender1), attacker.attackWeight (defender2));
}

TEST (test_11_00_blob_chooseNextAction_weights_t, attackWeight)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).smell (50.0).damage (110U);
	Blob defender = CreateBlob ().position (make_pt (9.0, 12.0)).HP (100U);

	EXPECT_DOUBLE_EQ (attacker.attackWeight (defender), 0.8 * 1.0 / 21.0);
}

TEST (test_11_00_blob_chooseNextAction_weights_t, fleeWeight)
{
	Blob attacker = CreateBlob ().position (make_pt (9.0, 12.0)).damage (110U);
	Blob defender = CreateBlob ().position  (make_pt (3.0, 4.0)).smell (50.0).HP (100U);

	EXPECT_DOUBLE_EQ (defender.fleeWeight (attacker), 0.8 * 1.0 / 21.0);
}

TEST (test_11_00_blob_chooseNextAction_weights_t, fleeWeight_scalesWithDistance)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).damage (100U);
	Blob defender1 = CreateBlob ().position (make_pt (10.0, 20.0)).smell (100.0).HP (50U);
	Blob defender2 = CreateBlob ().position (make_pt (20.0, 40.0)).smell (100.0).HP (50U);

	EXPECT_GT (defender1.fleeWeight (attacker), defender2.fleeWeight (attacker));
}

TEST (test_11_00_blob_chooseNextAction_weights_t, distance_does_not_affect_fleeWeight_in__same_square)
{
	Blob attacker = CreateBlob ().position (make_pt (3.0, 4.0)).damage (100U);
	Blob defender1 = CreateBlob ().position (make_pt (3.1, 4.0)).smell (100.0).HP (50U);
	Blob defender2 = CreateBlob ().position (make_pt (3.9, 4.0)).smell (100.0).HP (50U);

	EXPECT_DOUBLE_EQ (defender1.fleeWeight (attacker), defender2.fleeWeight (attacker));
}

TEST (test_11_00_blob_chooseNextAction_weights_t, distance_does_not_affect_attackWeight_in__same_square)
{
	Blob attacker1 = CreateBlob ().position (make_pt (3.9, 4.0)).damage (100U);
	Blob attacker2 = CreateBlob ().position (make_pt (3.1, 4.0)).damage (100U);
	Blob defender = CreateBlob ().position (make_pt (3.0, 4.0)).smell (100.0).HP (50U);

	EXPECT_DOUBLE_EQ (attacker1.attackWeight (defender), attacker2.attackWeight (defender));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

