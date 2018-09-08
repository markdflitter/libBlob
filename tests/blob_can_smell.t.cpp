#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, can_not_smell)
{
	Blob b1 ("", [](double) {return 0;}, 3, 4, 0, 0, 4);
	Blob b2 ("", [](double) {return 0;}, 6, 8, 0, 0, 4);

	ASSERT_FALSE (b1.canSmell (b2));
	ASSERT_FALSE (b2.canSmell (b1));
}

TEST (Blob, can_smell)
{
	Blob b1 {"", [](double) {return 0;}, 3, 4, 0, 0, 5};
	Blob b2 {"", [](double) {return 0;}, 6, 8, 0, 0, 4};

	ASSERT_TRUE (b1.canSmell (b2));
	ASSERT_FALSE (b2.canSmell (b1));
}

TEST (Blob, can_smell_each_other)
{
	Blob b1 {"", [](double) {return 0;}, 3, 4, 0, 0, 5};
	Blob b2 {"", [](double) {return 0;}, 6, 8, 0, 0, 5};

	ASSERT_TRUE (b1.canSmell (b2));
	ASSERT_TRUE (b2.canSmell (b1));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

