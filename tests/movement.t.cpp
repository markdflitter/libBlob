#include <gtest/gtest.h>
#include <random>
#include <blob.h>
#include <movement.h>

constexpr double threshold = 0.00001;

double fixed_angle (double previousMoveDirection)
{
	return previousMoveDirection + M_PI / 4;
};

TEST(Movement, equal)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10.1, 20.2, 0, 0, 0};

	Movement m (&b1, "a", 10, 20);
	ASSERT_TRUE (m == m);

	Movement m1 (&b1, "b", 10, 20);
	ASSERT_FALSE (m == m1);

	Movement m2 (&b1, "a", 30, 20);
	ASSERT_FALSE (m == m2);

	Movement m3 (&b1, "a", 10, 40);
	ASSERT_FALSE (m == m3);

	Movement m4 (&b2, "a", 10, 20);
	ASSERT_FALSE (m == m4);
}

TEST(Movement, not_equal)
{
	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 0, 0, 0};
	Blob b2 {"annette", fixed_angle, 10.1, 20.2, 0, 0, 0};

	Movement m (&b1, "a", 10, 20);
	ASSERT_FALSE (m != m);

	Movement m1 (&b1, "b", 10, 20);
	ASSERT_TRUE (m != m1);

	Movement m2 (&b1, "a", 30, 20);
	ASSERT_TRUE (m != m2);

	Movement m3 (&b1, "a", 10, 40);
	ASSERT_TRUE (m != m3);

	Movement m4 (&b2, "a", 10, 20);
	ASSERT_TRUE (m != m4);
}


TEST(Movement, copy_construct)
{
  	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 0, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (m);

	ASSERT_EQ (m,m2);
}

TEST(Movement, move_construct)
{
  	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 0, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (Movement (&b1, "a", 10, 20));
	
	ASSERT_EQ (m, m2);
}

TEST(Movement, assign)
{
  	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 0, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (&b1, "c", 10, 20);
	m2 = m;
	
	ASSERT_EQ (m, m2);
}

TEST(Movement, move_assign)
{
  	Blob b1 {"mark", fixed_angle, 10.1, 20.2, 0, 0, 0};
	Movement m (&b1, "a", 10, 20);
	Movement m2 (&b1, "c", 10, 20);
	m2 = Movement (&b1, "a", 10, 20);
	
	ASSERT_EQ (m, m2);
}

TEST (Movement, output)
{
	Blob b {"mark", fixed_angle, 20, 40, 5, 100, 0};
	std::shared_ptr<Action> a (new Movement (&b, "hello", 10.0, M_PI / 2));
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	std::stringstream s;

	s << *m;

	ASSERT_EQ (s.str (), "hello,10,90");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
