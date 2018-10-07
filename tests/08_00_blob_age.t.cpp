#include <gtest/gtest.h>
#include <blob.h>

TEST (test_08_00_blob_age_t, grows_older)
{
	Blob b1 = CreateBlob ().HP (100U).lifespan (100U);
	EXPECT_EQ (b1.age (), 0U);
	
	b1.growOlder ();
	EXPECT_EQ (b1.age (), 1U);
}

TEST (test_08_00_blob_age_t, dies_of_old_age)
{
	Blob b1 = CreateBlob ().lifespan (2U).HP (100U);
	
	EXPECT_EQ (b1.age (), 0U);
	
	b1.growOlder ();
	EXPECT_EQ (b1.age (), 1U);
	
	b1.growOlder ();
	EXPECT_EQ (b1.age (), 2U);
	EXPECT_TRUE (b1.isDead ());
}

TEST (test_08_00_blob_age_t, gets_older_when_moving)
{
	Blob b1 = CreateBlob ().HP (100U).lifespan (100U);
	EXPECT_EQ (b1.age (), 0U);
	
	b1.move (0.0, 0.0, "");
	EXPECT_EQ (b1.age (), 1U);
}

TEST (test_08_00_blob_age_t, gets_older_when_taking_damage)
{
	Blob b1 = CreateBlob ().HP (100U).lifespan (100U);
	EXPECT_EQ (b1.age (), 0U);
	
	b1.takeDamage (100);
	EXPECT_EQ (b1.age (), 1U);
}

TEST (test_08_00_blob_age_t, ageRatio)
{
	Blob b1 = CreateBlob ().lifespan (5U).HP (100U);
	EXPECT_DOUBLE_EQ (b1.ageRatio (), 1.0);
	
	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.ageRatio (), 0.86666666666666671);

	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.ageRatio (), 0.73333333333333328);
	
	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.ageRatio (), 0.6);
	
	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.ageRatio (), 0.46666666666666667);

	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.ageRatio (), 0.33333333333333331);
}

TEST (test_08_00_blob_age_t, blobs_get_slower_with_age)
{
	Blob b1 = CreateBlob ().lifespan (5U).speed (100.0).HP (100U);
	EXPECT_DOUBLE_EQ (b1.speed (), 100.0);

	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.speed (), 87.0);
}

TEST (test_08_00_blob_age_t, blobs_run_slower_with_age)
{
	Blob b1 = CreateBlob ().lifespan (5U).HP (100U).runningSpeed (100.0).HP (100U);
	EXPECT_DOUBLE_EQ (b1.runningSpeed (), 100.0);

	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.runningSpeed (), 87.0);
}

TEST (test_08_00_blob_age_t, blobs_smell_less_well_with_age)
{
	Blob b1 = CreateBlob ().lifespan (5U).HP (100U).smell (100.0);
	EXPECT_DOUBLE_EQ (b1.smell (), 100.0);

	b1.growOlder ();
	EXPECT_DOUBLE_EQ (b1.smell (), 86.66666666666671);
}

TEST (test_08_00_blob_age_t, damage_reduces_with_age)
{
	Blob b1 = CreateBlob ().lifespan (5U).damage (100.0).HP (100U);
	EXPECT_EQ (b1.baseDamage (), 100U);
	EXPECT_EQ (b1.damage (), 100U);

	b1.growOlder ();
	EXPECT_EQ (b1.baseDamage (), 100U);
	EXPECT_EQ (b1.damage (), 87U);
}



int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

