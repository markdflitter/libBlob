#include <gtest/gtest.h>
#include <blob.h>

TEST(Blob, kill)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 0, 0, 0, 0};
	b1.kill ();

	ASSERT_TRUE (b1.isDead ());
	ASSERT_TRUE (b1.state () == "dead");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

