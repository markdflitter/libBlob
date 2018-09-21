#include <gtest/gtest.h>
#include <blob.h>

TEST(Blob, kill)
{
	Blob b1 = CreateBlob ();
	EXPECT_FALSE (b1.isDead ());
	
	b1.kill ();

	EXPECT_TRUE (b1.isDead ());
	EXPECT_EQ (b1.state (), "dead");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

