#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, canSmellTrue)
{
	Blob b1 {"mark", [](double) {return 0;}, 3, 4, 100, 100, 5, 0};
	Blob b2 {"annette", [](double) {return 0;}, 6, 8, 100, 100, 5, 0};

	ASSERT_TRUE (b1.canSmell (b2));
	ASSERT_TRUE (b2.canSmell (b1));
}

TEST (Blob, canSmellFalse)
{
	Blob b1 {"mark", [](double) {return 0;}, 3, 4, 0, 0, 4, 0};
	Blob b2 {"annette", [](double) {return 0;}, 6, 8, 0, 0, 4, 0};

	ASSERT_FALSE (b1.canSmell (b2));
	ASSERT_FALSE (b2.canSmell (b1));
}

TEST (Blob, canSmellBoth)
{
	Blob b1 {"mark", [](double) {return 0;}, 3, 4, 0, 0, 4, 0};
	Blob b2 {"annette", [](double) {return 0;}, 6, 8, 0, 0, 5, 0};

	ASSERT_FALSE (b1.canSmell (b2));
	ASSERT_TRUE (b2.canSmell (b1));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

