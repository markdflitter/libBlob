#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, sameSquareTrue)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 20, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 20, 0, 0, 0, 0};

	ASSERT_TRUE (b1.sameSquare (b2));
	ASSERT_TRUE (b2.sameSquare (b1));
}

TEST (Blob, sameSquareFalse)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 20, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 20, 10, 0, 0, 0, 0};

	ASSERT_FALSE (b1.sameSquare (b2));
	ASSERT_FALSE (b2.sameSquare (b1));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

