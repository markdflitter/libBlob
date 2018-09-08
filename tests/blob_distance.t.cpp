#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, distance_equals_0)
{
	Blob b1 ("", [](double) {return 0;}, 10, 10);
	Blob b2 ("", [](double) {return 0;}, 10, 10);

	ASSERT_EQ (b1.distance (b2), 0);
	ASSERT_EQ (b2.distance (b1), 0);
}

TEST (Blob, distance_345_triangle_at_origin)
{
	Blob b1 ("", [](double) {return 0;}, 0, 0);
	Blob b2 ("", [](double) {return 0;}, 3, 4);

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distance_minus_345_triangle_at_origin)
{
	Blob b1 ("", [](double) {return 0;}, 0, 0);
	Blob b2 ("", [](double) {return 0;}, -3, -4);

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distance_345_triangle_off_origin)
{
	Blob b1 ("", [](double) {return 0;}, 3, 4);
	Blob b2 ("", [](double) {return 0;}, 6, 8);

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distance_minus_345_triangle_off_origin)
{
	Blob b1 ("", [](double) {return 0;}, -3, -4);
	Blob b2 ("", [](double) {return 0;}, -6, -8);

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

TEST (Blob, distance_minus_345_triangle_cross_origin)
{
	Blob b1 ("", [](double) {return 0;}, -2, -2);
	Blob b2 ("", [](double) {return 0;}, 1, 2);

	ASSERT_EQ (b1.distance (b2), 5);
	ASSERT_EQ (b2.distance (b1), 5);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

