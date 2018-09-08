#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, huntN)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 2, 4, 0, 0, 1};
	Blob b2 {"annette", [](double) {return 0;}, 5, 10, 12, 12, 0, 0, 1};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette (fast)", 4, 0));
}

TEST (Blob, huntS)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 2, 4, 0, 0, 1};
	Blob b2 {"annette", [](double) {return 0;}, 5, -10, 12, 12, 0, 0, 1};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette (fast)", 4, M_PI));
}

TEST (Blob, huntE)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 2, 4, 0, 0, 1};
	Blob b2 {"annette", [](double) {return 0;}, 10, 5, 12, 12, 0, 0, 1};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette (fast)", 4, M_PI/2));
}

TEST (Blob, huntW)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, 5, 2, 4, 0, 0, 1};
	Blob b2 {"annette", [](double) {return 0;}, -10, 5, 12, 12, 0, 0, 1};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&b1, "hunting annette (fast)", 4, 3 * M_PI / 2));
}

TEST (Blob, huntGetsCloser)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, 5, 7, 7, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, -10, 5, 12, 12, 0, 0};

	double d1 = b1.distance (b2);
	std::shared_ptr<Action> m = b1.hunt (b2);
	m->apply ();

	double d2 = b1.distance (b2);
	ASSERT_TRUE (d2 < d1);
}

TEST (Blob, huntCatches)
{
	Blob b1 {"mark", [](double) {return 0;}, -5, 5, 7, 7, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, -10, 5, 12, 12, 0, 0};

	std::shared_ptr<Action> a = b1.hunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr<Movement> m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (m->_speed < 7);
	a->apply ();

	ASSERT_TRUE (b1.isInSameSquare (b2));
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

