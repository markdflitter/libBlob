#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, distance_equals_0)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 10.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 10.0);

	EXPECT_DOUBLE_EQ (b1.distance (b2), 0.0);
	EXPECT_DOUBLE_EQ (b2.distance (b1), 0.0);
}

TEST (Blob, distance_345_triangle_at_origin)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	Blob b2 ("", [](double) {return 0.0;}, 3.0, 4.0);

	EXPECT_DOUBLE_EQ (b1.distance (b2), 5.0);
	EXPECT_DOUBLE_EQ (b2.distance (b1), 5.0);
}

TEST (Blob, distance_minus_345_triangle_at_origin)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	Blob b2 ("", [](double) {return 0.0;}, -3.0, -4.0);

	EXPECT_DOUBLE_EQ (b1.distance (b2), 5.0);
	EXPECT_DOUBLE_EQ (b2.distance (b1), 5.0);
}

TEST (Blob, distance_345_triangle_off_origin)
{
	Blob b1 ("", [](double) {return 0.0;}, 3.0, 4.0);
	Blob b2 ("", [](double) {return 0.0;}, 6.0, 8.0);

	EXPECT_DOUBLE_EQ (b1.distance (b2), 5.0);
	EXPECT_DOUBLE_EQ (b2.distance (b1), 5.0);
}

TEST (Blob, distance_minus_345_triangle_off_origin)
{
	Blob b1 ("", [](double) {return 0.0;}, -3.0, -4.0);
	Blob b2 ("", [](double) {return 0.0;}, -6, -8);

	EXPECT_DOUBLE_EQ (b1.distance (b2), 5.0);
	EXPECT_DOUBLE_EQ (b2.distance (b1), 5.0);
}

TEST (Blob, distance_minus_345_triangle_cross_origin)
{
	Blob b1 ("", [](double) {return 0.0;}, -2, -2);
	Blob b2 ("", [](double) {return 0.0;}, 1, 2);

	EXPECT_DOUBLE_EQ (b1.distance (b2), 5.0);
	EXPECT_DOUBLE_EQ (b2.distance (b1), 5.0);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

