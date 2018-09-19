#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, distanceWeight_sameSquare)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 1.0);
}

TEST (Blob, distanceWeight_smell_is_zero)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 0.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 0.0);
}

TEST (Blob, distanceWeight_out_of_range)
{
	Blob b1 ("", [](double) {return 0.0;}, 3.0, 4.0, 0.0, 0.0, 5.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 9.0, 12.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 0.0);
}

TEST (Blob, distanceWeight_in_range)
{
	Blob b1 ("", [](double) {return 0.0;}, 3.0, 4.0, 0.0, 0.0, 50.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 9.0, 12.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 0.80);
}

TEST (Blob, distanceWeight_closer_blobs_are_weighted_higher)
{
	Blob b1 ("", [](double) {return 0.0;}, 3.0, 4.0, 0.0, 0.0, 50.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 6.0, 8.0, 0.0, 0.0, 0.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 9.0, 12.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_GT (b1.distanceWeight(b2), b1.distanceWeight (b3));
}

TEST (Blob, distanceWeight_better_smell_gives_higher_weight)
{
	Blob b1 ("", [](double) {return 0.0;}, 3.0, 4.0, 0.0, 0.0, 50.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 3.0, 4.0, 0.0, 0.0, 100.0, 100U);
	Blob b3 ("", [](double) {return 0.0;}, 9.0, 12.0, 0.0, 0.0, 0.0, 100U);

	EXPECT_GT (b2.distanceWeight(b3), b1.distanceWeight (b3));
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

