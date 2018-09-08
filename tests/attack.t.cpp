#include <attack.h>
#include <gtest/gtest.h>
#include <memory>
#include <blob.h>

class AttackableMock : public Attackable
{
public:
	void attack (unsigned int strength)
	{
		_strength = strength;
	}

	double _strength = 0;
};

TEST(Attack, equal)
{
	AttackableMock am1;
	AttackableMock am2;	

	Attack a (&am1, 10);
	ASSERT_TRUE (a == a);

	Attack a0 (&am1, 10);
	ASSERT_TRUE (a == a0);

	Attack a1 (&am1, 20);
	ASSERT_FALSE (a == a1);

	Attack a2 (&am2, 10);
	ASSERT_FALSE (a == a2);
}

TEST(Attack, not_equal)
{
	AttackableMock am1;
	AttackableMock am2;	

	Attack a (&am1, 10);
	ASSERT_FALSE (a != a);

	Attack a1 (&am1, 20);
	ASSERT_TRUE (a != a1);

	Attack a2 (&am2, 10);
	ASSERT_TRUE (a != a2);
}

TEST (Attack, output)
{
	AttackableMock am1;
	std::shared_ptr<Action> a (new Attack (&am1, 10.0));
	ASSERT_TRUE (std::dynamic_pointer_cast <Attack> (a));
	std::shared_ptr <Attack> m (std::dynamic_pointer_cast <Attack> (a));
	
	std::stringstream s;

	s << *m;

	ASSERT_EQ (s.str (), "10");
}

TEST (Attack, apply)
{
	AttackableMock am1;
	std::shared_ptr<Action> a (new Attack (&am1, 10.0));
	
	a->apply ();
	ASSERT_TRUE (am1._strength = 10.0);
}

TEST (Attack, attack)
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
