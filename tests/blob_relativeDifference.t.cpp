#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, relativeDifference_zero)
{
	Blob b;
	EXPECT_DOUBLE_EQ (b.relativeDifference (1.0, 0.0), 0.5);
	EXPECT_DOUBLE_EQ (b.relativeDifference (0.0, 1.0), -0.5);
}

TEST (Blob, relativeDifference_non_zero)
{
	Blob b;
	EXPECT_DOUBLE_EQ (b.relativeDifference (50.0, 50.0), 0.0);
	EXPECT_DOUBLE_EQ (b.relativeDifference (100.0, 50.0), 1.0 / 6.0);
	EXPECT_DOUBLE_EQ (b.relativeDifference (50.0, 100.0), -1.0 / 6.0);
}

TEST (Blob, relativeDifference_negative_asserts)
{
	Blob b;
	EXPECT_DEATH (b.relativeDifference (-50.0, 50.0), "");
	EXPECT_DEATH (b.relativeDifference (50.0, -50.0), "");
	EXPECT_DEATH (b.relativeDifference (-50.0, -50.0), "");
}

TEST (Blob, relativeDifference_magnitude)
{
	Blob b;
	EXPECT_GT (b.relativeDifference (1000, 50), b.relativeDifference (100, 50));
	EXPECT_GT (b.relativeDifference (1000, 50), b.relativeDifference (1000, 500));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

