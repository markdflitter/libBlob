#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, growsOlder)
{
	Blob b1 = CreateBlob ();
	EXPECT_EQ (b1.age (), 0U);
	b1.growOlder ();
	EXPECT_EQ (b1.age (), 1U);
}

TEST (Blob, dies_of_old_age)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0.0, 2U);
	EXPECT_EQ (b1.age (), 0U);
	b1.growOlder ();
	EXPECT_EQ (b1.age (), 1U);
	b1.growOlder ();
	EXPECT_EQ (b1.age (), 2U);
	EXPECT_TRUE (b1.isDead ());
}

TEST (Blob, blob_gets_older_when_moving)
{
	Blob b1 = CreateBlob ();
	EXPECT_EQ (b1.age (), 0U);
	b1.move (0.0, 0.0, "");
	EXPECT_EQ (b1.age (), 1U);
}

TEST (Blob, blob_gets_older_when_taking_damage)
{
	Blob b1 = CreateBlob ();
	EXPECT_EQ (b1.age (), 0U);
	b1.takeDamage (100);
	EXPECT_EQ (b1.age (), 1U);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

