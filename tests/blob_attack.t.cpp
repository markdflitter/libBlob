#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, hunts_if_not_in_same_square)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 20.0, 20.0, 0.0, 0.0, 0.0, 100U);

	std::shared_ptr<Action> a = b1.createActionAttack (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));

	EXPECT_EQ (m->_reason, "hunting  (fast)");
}

TEST (Blob, fights_if_in_same_square)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 110U);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 100U);

	std::shared_ptr<Action> a = b1.createActionAttack (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Fight> (a));
	std::shared_ptr <Fight> m (std::dynamic_pointer_cast <Fight> (a));
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

