#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, is_in_range_dx_false)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 0.0);

	ASSERT_FALSE (b1.isInRange (b2, 9.0));
	ASSERT_FALSE (b2.isInRange (b1, 9.0));
}

TEST (Blob, is_in_range_dx_true)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 0.0);

	ASSERT_TRUE (b1.isInRange (b2, 10.0));
	ASSERT_TRUE (b2.isInRange (b1, 10.0));
}

TEST (Blob, is_in_range_dy_false)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 10.0);

	ASSERT_FALSE (b1.isInRange (b2, 9.0));
	ASSERT_FALSE (b2.isInRange (b1, 9.0));
}

TEST (Blob, is_in_range_dy_true)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 10.0);

	ASSERT_TRUE (b1.isInRange (b2, 10.0));
	ASSERT_TRUE (b2.isInRange (b1, 10.0));
}

TEST (Blob, is_in_range_dxy_false)
{
	Blob b1 {"", [](double) {return 0.0;}, 3.0, 4.0};
	Blob b2 {"", [](double) {return 0.0;}, 6.0, 8.0};

	ASSERT_FALSE (b1.isInRange (b2, 4.0));
	ASSERT_FALSE (b2.isInRange (b1, 4.0));
}

TEST (Blob, is_in_range_dxy_true)
{
	Blob b1 {"", [](double) {return 0.0;}, 3.0, 4.0};
	Blob b2 {"", [](double) {return 0.0;}, 6.0, 8.0};

	ASSERT_TRUE (b1.isInRange (b2, 5.0));
	ASSERT_TRUE (b2.isInRange (b1, 5.0));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

