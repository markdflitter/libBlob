#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, is_in_same_square_false)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 20.0);
	Blob b2 ("", [](double) {return 0.0;}, 20.0, 10.0);

	ASSERT_FALSE (b1.isInSameSquare (b2));
	ASSERT_FALSE (b2.isInSameSquare (b1));
}

TEST (Blob, is_in_same_square_true_identical_position)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 20.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 20.0);

	ASSERT_TRUE (b1.isInSameSquare (b2));
	ASSERT_TRUE (b2.isInSameSquare (b1));
}

TEST (Blob, is_in_same_square_true_different_position)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.1);
	Blob b2 ("", [](double) {return 0.0;}, 10.9, 20.9);

	ASSERT_TRUE (b1.isInSameSquare (b2));
	ASSERT_TRUE (b2.isInSameSquare (b1));
}

TEST (Blob, is_in_same_square_true_minus_different_position)
{
	Blob b1 ("", [](double) {return 0.0;}, -10.1, -20.1);
	Blob b2 ("", [](double) {return 0.0;}, -10.9, -20.9);

	ASSERT_TRUE (b1.isInSameSquare (b2));
	ASSERT_TRUE (b2.isInSameSquare (b1));
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

