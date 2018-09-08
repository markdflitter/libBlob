#include <gtest/gtest.h>
#include <blob.h>

TEST(Blob, kill)
{
	Blob b1;
	ASSERT_FALSE (b1.isDead ());
	
	b1.kill ();

	ASSERT_TRUE (b1.isDead ());
	ASSERT_EQ (b1.state (), "dead");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

