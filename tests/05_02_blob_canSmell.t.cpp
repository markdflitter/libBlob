#include <gtest/gtest.h>
#include <blob.h>

TEST (test_05_02_blob_canSmell_t, can_not_smell)
{
	Blob b1 = CreateBlob ().position (make_pt (3.0, 4.0)).smell (4.0);
	Blob b2 = CreateBlob ().position (make_pt (6.0, 8.0)).smell (4.0);

	EXPECT_FALSE (b1.canSmell (b2));
	EXPECT_FALSE (b2.canSmell (b1));
}

TEST (test_05_02_blob_canSmell_t, can_smell)
{
	Blob b1 = CreateBlob ().position (make_pt (3.0, 4.0)).smell (5.0);
	Blob b2 = CreateBlob ().position (make_pt (6.0, 8.0)).smell (4.0);

	EXPECT_TRUE (b1.canSmell (b2));
	EXPECT_FALSE (b2.canSmell (b1));
}

TEST (test_05_02_blob_canSmell_t, can_smell_each_other)
{
	Blob b1 = CreateBlob ().position (make_pt (3.0, 4.0)).smell (5.0);
	Blob b2 = CreateBlob ().position (make_pt (6.0, 8.0)).smell (5.0);

	EXPECT_TRUE (b1.canSmell (b2));
	EXPECT_TRUE (b2.canSmell (b1));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
