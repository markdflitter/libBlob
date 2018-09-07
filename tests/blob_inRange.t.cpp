#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, inRangex)
{
	Blob b1 {"mark", [](double) {return 0;}, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 0, 0, 0, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 9));
	ASSERT_FALSE (b2.inRange (b1, 9));

	ASSERT_TRUE (b1.inRange (b2, 10));
	ASSERT_TRUE (b2.inRange (b1, 10));
}

TEST (Blob, inRangey)
{
	Blob b1 {"mark", [](double) {return 0;}, 0, 0, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 0, 10, 0, 0, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 9));
	ASSERT_FALSE (b2.inRange (b1, 9));

	ASSERT_TRUE (b1.inRange (b2, 10));
	ASSERT_TRUE (b2.inRange (b1, 10));
}

TEST (Blob, inRangexy)
{
	Blob b1 {"mark", [](double) {return 0;}, 3, 4, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 6, 8, 0, 0, 0, 0};

	ASSERT_FALSE (b1.inRange (b2, 4));
	ASSERT_FALSE (b2.inRange (b1, 4));

	ASSERT_TRUE (b1.inRange (b2, 5));
	ASSERT_TRUE (b2.inRange (b1, 5));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

