#include <gtest/gtest.h>
#include <blob.h>

TEST (test_07_02_blob_fight_t, takesDamage)
{
	Blob b = CreateBlob ().HP (100U).lifespan (10U);
	EXPECT_EQ (b.HP (), 100U);
	EXPECT_FALSE (b.isDead ());

	b.takeDamage (1U);
	EXPECT_EQ (b.HP (), 99U);
	EXPECT_FALSE (b.isDead ());
}

TEST (test_07_02_blob_fight_t, kill)
{
	Blob b = CreateBlob ().HP (100U).lifespan (10U);
	EXPECT_EQ (b.HP (), 100U);
	EXPECT_FALSE (b.isDead ());

	b.takeDamage (100U);
	EXPECT_EQ (b.HP (), 0U);
	EXPECT_TRUE (b.isDead ());
}

TEST (test_07_02_blob_fight_t, overkill)
{
	Blob b = CreateBlob ().HP (100U).lifespan (10U);
	EXPECT_EQ (b.HP (), 100U);
	EXPECT_FALSE (b.isDead ());

	b.takeDamage (1000U);
	EXPECT_EQ (b.HP (), 0U);
	EXPECT_TRUE (b.isDead ());
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

