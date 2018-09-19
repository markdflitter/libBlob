#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, attackWeight)
{
	Blob b1 ("", [](double) {return 0.0;}, 3.0, 4.0, 0.0, 0.0, 50.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 9.0, 12.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.attackWeight (b2), 0.8 * 1.0 / 21.0);
}

TEST (Blob, fleeWeight)
{
	Blob b1 ("", [](double) {return 0.0;}, 3.0, 4.0, 0.0, 0.0, 50.0, 100U);
	Blob b2 ("", [](double) {return 0.0;}, 9.0, 12.0, 0.0, 0.0, 0.0, 110U);

	EXPECT_DOUBLE_EQ (b1.fleeWeight (b2), 0.8 * 1.0 / 21.0);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

