#include <movement.h>
#include <gtest/gtest.h>
#include <memory>

class MoveableMock : public Moveable
{
public:
	void move (double speed, double angleInRadians, const std::string& reason)
	{
		_speed = speed;
		_angleInRadians = angleInRadians;
		_reason = reason;	
	}

	double _speed = 0;
	double _angleInRadians = 0;
	std::string _reason;
};

TEST(Movement, equal)
{
	MoveableMock mm1;
	MoveableMock mm2;	

	Movement m (&mm1, "a", 10, 20);
	ASSERT_TRUE (m == m);

	Movement m0 (&mm1, "a", 10, 20);
	ASSERT_TRUE (m == m0);

	Movement m1 (&mm1, "b", 10, 20);
	ASSERT_FALSE (m == m1);

	Movement m2 (&mm1, "a", 30, 20);
	ASSERT_FALSE (m == m2);

	Movement m3 (&mm1, "a", 10, 40);
	ASSERT_FALSE (m == m3);

	Movement m4 (&mm2, "a", 10, 20);
	ASSERT_FALSE (m == m4);
}

TEST(Movement, not_equal)
{
	MoveableMock mm1;
	MoveableMock mm2;	

	Movement m (&mm1, "a", 10, 20);
	ASSERT_FALSE (m != m);

	Movement m1 (&mm1, "b", 10, 20);
	ASSERT_TRUE (m != m1);

	Movement m2 (&mm1, "a", 30, 20);
	ASSERT_TRUE (m != m2);

	Movement m3 (&mm1, "a", 10, 40);
	ASSERT_TRUE (m != m3);

	Movement m4 (&mm2, "a", 10, 20);
	ASSERT_TRUE (m != m4);
}

TEST (Movement, output)
{
	MoveableMock mm1;
	std::shared_ptr<Action> a (new Movement (&mm1, "hello", 10.0, M_PI / 2));
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	std::stringstream s;

	s << *m;

	ASSERT_EQ (s.str (), "hello,10,90");
}

TEST (Movement, apply)
{
	MoveableMock mm1;
	std::shared_ptr<Action> a (new Movement (&mm1, "hello", 10.0, M_PI / 2));
	
	a->apply ();
	ASSERT_TRUE (mm1._speed = 10.0);
	ASSERT_TRUE (mm1._angleInRadians == M_PI/2);
	ASSERT_TRUE (mm1._reason == "hello");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
