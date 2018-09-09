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

TEST(Attack, create)
{
	AttackableMock am;
	Attack a (&am, 10U);
	EXPECT_EQ (a._target, &am);
	EXPECT_EQ (a._strength, 10U);
}

TEST(Attack, equal_to_self)
{
	AttackableMock am;
	Attack a (&am, 10U);
	EXPECT_TRUE (a == a);
}

TEST (Attack, equal_to_other)
{
	AttackableMock am;
	Attack a1 (&am, 10U);
	Attack a2 (&am, 10U);
	EXPECT_TRUE (a1 == a2);
}

TEST (Attack, equal_false_different_attackable)
{
	AttackableMock am1;
	AttackableMock am2;
	Attack a1 (&am1, 10U);
	Attack a2 (&am2, 10U);
	EXPECT_FALSE (a1 == a2);
}

TEST (Attack, equal_false_different_strength)
{
	AttackableMock am;
	Attack a1 (&am, 10U);
	Attack a2 (&am, 20U);
	EXPECT_FALSE (a1 == a2);
}

TEST(Attack, not_equal_equal_to_self)
{
	AttackableMock am;
	Attack a (&am, 10U);
	EXPECT_FALSE (a != a);
}

TEST(Attack, not_equal_different_attackable)
{
	AttackableMock am1;
	AttackableMock am2;
	Attack a1 (&am1, 10U);
	Attack a2 (&am2, 10U);
	EXPECT_TRUE (a1 != a2);
}

TEST(Attack, not_equal_different_strength)
{
	AttackableMock am;
	Attack a1 (&am, 10U);
	Attack a2 (&am, 20U);
	EXPECT_TRUE (a1 != a2);
}

TEST (Attack, output)
{
	AttackableMock am1;
	std::shared_ptr<Action> a (new Attack (&am1, 10U));
	EXPECT_TRUE (std::dynamic_pointer_cast <Attack> (a));
	std::shared_ptr <Attack> m (std::dynamic_pointer_cast <Attack> (a));
	
	std::stringstream s;

	s << *m;

	EXPECT_EQ (s.str (), "10");
}

TEST (Attack, apply)
{
	AttackableMock am1;
	std::shared_ptr<Action> a (new Attack (&am1, 10));
	
	a->apply ();
	EXPECT_EQ (am1._strength, 10U);
}

TEST (Attack, applies_to_blob)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 10);

	std::shared_ptr <Action> a = b2.createActionAttack (b1);
	a->apply ();

	EXPECT_EQ (b1.strength (), 90);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
