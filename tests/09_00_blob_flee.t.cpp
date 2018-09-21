#include <gtest/gtest.h>
#include <blob.h>

TEST (test_09_00_blob_flee, flee)
{
	Blob runner = CreateBlob ().runningSpeed (13.0);
	Blob runningFrom = CreateBlob ();

	std::shared_ptr<Action> a = runner.createActionFlee (runningFrom);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&runner, "running from  (fast)", 13.0, 0.0));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

