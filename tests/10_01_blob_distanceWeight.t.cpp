#include <gtest/gtest.h>
#include <blob.h>

TEST (test_10_01_blob_distanceWeight_t, sameSquare)
{
	Blob b1 = CreateBlob ();
	Blob b2 = CreateBlob ();

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 1.0);
}

TEST (test_10_01_blob_distanceWeight_t, smell_is_zero)
{
	Blob b1 = CreateBlob ().position (make_pt (10.0, 0.0));
	Blob b2 = CreateBlob ();

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 0.0);
}

TEST (test_10_01_blob_distanceWeight_t, out_of_range)
{
	Blob b1 = CreateBlob ().position (make_pt (3.0, 4.0)).smell (5.0);
	Blob b2 = CreateBlob ().position (make_pt (9.0, 12.0));

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 0.0);
}

TEST (test_10_01_blob_distanceWeight_t, in_range)
{
	Blob b1 = CreateBlob ().position (make_pt (3.0, 4.0)).smell (50.0);
	Blob b2 = CreateBlob ().position (make_pt (9.0, 12.0));

	EXPECT_DOUBLE_EQ (b1.distanceWeight(b2), 0.80);
}

TEST (test_10_01_blob_distanceWeight_t, closer_blobs_are_weighted_higher)
{
	Blob base = CreateBlob ().position (make_pt (3.0, 4.0)).smell (50.0);
	Blob near = CreateBlob ().position (make_pt (6.0, 8.0));
	Blob far = CreateBlob ().position (make_pt (9.0, 12.0));

	EXPECT_GT (base.distanceWeight(near), base.distanceWeight (far));
}

TEST (test_10_01_blob_distanceWeight_t, better_smell_gives_higher_weight)
{
	Blob target = CreateBlob ().position (make_pt (9.0, 12.0));
	Blob lowSmellRange = CreateBlob ().position (make_pt (3.0, 4.0)).smell (50.0);
	Blob highSmellRange = CreateBlob ().position (make_pt (3.0, 4.0)).smell (100.0);

	EXPECT_GT (highSmellRange.distanceWeight(target), lowSmellRange.distanceWeight (target));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

