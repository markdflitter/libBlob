#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, ages)
{
	std::vector<Blob> blobs {Blob ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0.0, 100U)};
	EXPECT_EQ (blobs[0].age (), 0U);
	b1.chooseNextAction (blobs);
	EXPECT_EQ (blobs[0].age (), 1U);
}

TEST (Blob, dies_of_old_ages)
{
	std::vector<Blob> blobs {Blob ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0.0, 2U)};
	EXPECT_EQ (blobs[0].age (), 0U);
	b1.chooseNextAction (blobs);
	EXPECT_EQ (blobs[0].age (), 1U);
	b1.chooseNextAction (blobs);
	EXPECT_EQ (blobs[0].age (), 2U);
	EXPECT_TRUE (blobs[0].isDead ());
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

