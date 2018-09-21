#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, flee)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 13.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 15.0, 12.0, 12.0);

	std::shared_ptr<Action> a = b1.createActionFlee (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&b1, "running from  (fast)", 13.0, 0.0));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

