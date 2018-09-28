#include <gtest/gtest.h>
#include <blob.h>
// refactor sorting into a separatae function and test it

TEST (test_00_00_template_t, gtest)
{
	EXPECT_TRUE(true);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

