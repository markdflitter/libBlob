#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, distance0)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 0);
	ASSERT_EQ (b2.distance (b1), 0);
}

TEST (Blob, distance345)
{
	Blob b1 {"mark", [](double) {return 0;}, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 3, 4, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distancen345)
{
	Blob b1 {"mark", [](double) {return 0;}, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, -3, -4, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distance345_2)
{
	Blob b1 {"mark", [](double) {return 0;}, 3, 4, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 6, 8, 0, 0, 0, 0};

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

