#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, attack_without_killing)
{
	Blob b1 ("", [](double) {return 0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	ASSERT_EQ (b1.strength (), 100U);
	
	b1.attack (10U);
	ASSERT_EQ (b1.strength (), 90U);
	ASSERT_FALSE (b1.isDead ());
}

TEST (Blob, attack_and_kill)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 20U);
	ASSERT_EQ (b1.strength (), 20U);
		
	b1.attack (10U);
	ASSERT_EQ (b1.strength (), 10U);
	ASSERT_FALSE (b1.isDead ());
	
	b1.attack (10U);
	ASSERT_EQ (b1.strength (), 0U);
	ASSERT_TRUE (b1.isDead ());
}

TEST (Blob, attack_and_overkill)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 20U);
	ASSERT_EQ (b1.strength (), 20U);
		
	b1.attack (100U);
	ASSERT_EQ (b1.strength (), 0U);
	ASSERT_TRUE (b1.isDead ());
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

