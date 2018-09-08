#include <gtest/gtest.h>
#include <blob.h>

constexpr double threshold = 0.00001;

TEST (Blob, flee)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 5, 5, 10, 0, 0, 2};
	Blob b2 {"annette", [](double) {return 0;}, 5, 10, 12, 12, 0, 0};

	b1.move (5, 3 * M_PI/2, "wandering");	

	std::shared_ptr<Action> a = b1.flee (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_target == &b1);
	ASSERT_TRUE (m->_reason == "running from annette (fast)");
	ASSERT_TRUE (m->_speed == 10);
	ASSERT_TRUE (fabs (m->_angleInRadians) - ((0.9 * 3 * M_PI / 2) + (0.1 * M_PI) + M_PI / 4) < threshold);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

