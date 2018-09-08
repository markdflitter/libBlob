#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, attack_no_kill)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 100};
	
	b1.attacked (10);
	ASSERT_TRUE (b1.strength () == 90);
	ASSERT_TRUE (!b1.isDead ());
}

TEST (Blob, attack_and_kill)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 20};
	
	b1.attacked (10);
	ASSERT_TRUE (b1.strength () == 10);
	ASSERT_TRUE (!b1.isDead ());
	
	b1.attacked (10);
	ASSERT_TRUE (b1.strength () == 0);
	ASSERT_TRUE (b1.isDead ());
}

TEST (Blob, attack)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, 5, 7, 7, 0, 100};
	Blob b2 {"annette", [](double) {return 0;}, -10, 5, 12, 12, 0, 10};

	std::shared_ptr <Action> a = b2.attack (b1);
	a->apply ();

	ASSERT_TRUE (b1.strength () == 90);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

