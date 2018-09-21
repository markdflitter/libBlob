#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, dead_blobs_do_nothing)
{
	std::vector<Blob> blobs {CreateBlob ()};

	std::shared_ptr<Action> a1 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a1));
	std::shared_ptr <Movement> m1 (std::dynamic_pointer_cast <Movement> (a1));
	EXPECT_EQ (*m1, Movement (&blobs[0],"wandering", 0.0, 0.0));

	blobs[0].kill ();
	
	std::shared_ptr<Action> a2 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a2));
	std::shared_ptr <Movement> m2 (std::dynamic_pointer_cast <Movement> (a2));
	EXPECT_EQ (*m2, Movement (&blobs[0],"dead",0,0));
}


TEST (Blob, dead_blobs_do_not_age)
{
	std::vector<Blob> blobs {Blob ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0U, 0U, 0.0, 2U)};
	EXPECT_EQ (blobs[0].age (), 0U);
	blobs[0].kill ();	
	blobs[0].chooseNextAction (blobs);
	EXPECT_EQ (blobs[0].age (), 0U);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

