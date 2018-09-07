#include <gtest/gtest.h>
#include <blob.h>

constexpr double threshold = 0.00001;

TEST (Blob, angleN)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 5, 10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 0.0f) < threshold);
}

TEST (Blob, angleS)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, -5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, -5, -10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - M_PI) < threshold);
}

TEST (Blob, angleE)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 5, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - M_PI / 2) < threshold);
}

TEST (Blob, angleW)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, -10, 5, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 3*M_PI/2) < threshold);
}

TEST (Blob, angleNE)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - M_PI/4) < threshold);
}

TEST (Blob, angleNW)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, 5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, -10, 10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - -M_PI/4) < threshold);
}

TEST (Blob, angleSE)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, -5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, -10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 3 * M_PI/4) < threshold);
}

TEST (Blob, angleSW)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, -5, 0, 0, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, -10, -10, 0, 0, 0, 0};

	double angle = b1.angle (b2);
	ASSERT_TRUE (fabs (angle - 5 * M_PI/4) < threshold);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

