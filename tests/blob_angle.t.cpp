#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, angle_north)
{
	Blob b1 ("", [](double) {return 0.0;}, 5.0, 5.0);
	Blob b2 ("", [](double) {return 0.0;}, 5.0, 10.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, 0.0);
}

TEST (Blob, angle_south)
{
	Blob b1 ("", [](double) {return 0.0;}, -5.0, -5.0);
	Blob b2 ("", [](double) {return 0.0;}, -5.0, -10.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, M_PI);
}

TEST (Blob, angle_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 5.0, 5.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 5.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, M_PI / 2.0);
}

TEST (Blob, angle_west)
{
	Blob b1 ("", [](double) {return 0;}, -5.0, 5.0);
	Blob b2 ("", [](double) {return 0;}, -10.0, 5.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, 3.0 * M_PI / 2.0);
}

TEST (Blob, angle_north_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 5.0, 5.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 10.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, M_PI / 4);
}

TEST (Blob, angle_north_west)
{
	Blob b1 ("", [](double) {return 0.0;}, -5.0, 5.0);
	Blob b2 ("", [](double) {return 0.0;}, -10.0, 10.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, -M_PI / 4);
}

TEST (Blob, angle_south_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 5.0, -5.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, -10.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, 3 * M_PI / 4);
}

TEST (Blob, angle_south_west)
{
	Blob b1 ("", [](double) {return 0.0;}, -5.0, -5.0);
	Blob b2 ("", [](double) {return 0.0;}, -10.0, -10.0);

	double angle = b1.angle (b2);
	ASSERT_EQ (angle, 5 * M_PI / 4);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

