#include <attack.h>
#include <gtest/gtest.h>
#include <memory>
#include <blob.h>

class TargetMock : public Target
{
public:
	TargetMock (unsigned int damage) :
		_damage (damage) 
	{
	}

	unsigned int damage () const
	{
		return _damage;
	}

	void attack (unsigned int damage)
	{
		_damageTaken = damage;
	}

	unsigned int _damageTaken = 0;
	unsigned int _damage = 0;
};

TEST(Attack, create)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a (&tm1, &tm2);
	EXPECT_EQ (a._target, &tm1);
	EXPECT_EQ (a._attacker, &tm2);
}

TEST(Attack, equal_to_self)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a (&tm1, &tm2);
	EXPECT_TRUE (a == a);
}

TEST (Attack, equal_to_other)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a1 (&tm1, &tm2);
	Attack a2 (&tm1, &tm2);
	EXPECT_TRUE (a1 == a2);
}

TEST (Attack, equal_false_different_target)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a1 (&tm1, &tm2);
	Attack a2 (&tm2, &tm2);
	EXPECT_FALSE (a1 == a2);
}

TEST (Attack, equal_false_different_attacker)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a1 (&tm1, &tm2);
	Attack a2 (&tm1, &tm1);
	EXPECT_FALSE (a1 == a2);
}

TEST(Attack, not_equal_equal_to_self)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a (&tm1, &tm2);
	EXPECT_FALSE (a != a);
}

TEST(Attack, not_equal_different_target)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a1 (&tm1, &tm2);
	Attack a2 (&tm2, &tm2);
	EXPECT_TRUE (a1 != a2);
}

TEST(Attack, not_equal_different_attacker)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Attack a1 (&tm1, &tm2);
	Attack a2 (&tm1, &tm1);
	EXPECT_TRUE (a1 != a2);
}

TEST (Attack, output)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	std::shared_ptr<Action> a (new Attack (&tm1, &tm2));
	EXPECT_TRUE (std::dynamic_pointer_cast <Attack> (a));
	std::shared_ptr <Attack> m (std::dynamic_pointer_cast <Attack> (a));
	
	std::stringstream s;

	s << *m;

	EXPECT_EQ (s.str (), "20");
}

TEST (Attack, apply_target_is_damaged)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	std::shared_ptr<Action> a (new Attack (&tm1, &tm2));
	
	a->apply ();
	EXPECT_EQ (tm1._damageTaken, 20U);
}

TEST (Attack, apply_attacker_is_damaged)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	std::shared_ptr<Action> a (new Attack (&tm1, &tm2));
	
	a->apply ();
	EXPECT_EQ (tm2._damageTaken, 10U);
}


TEST (Attack, applies_to_blobs)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100);
	Blob b2 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 5);

	std::shared_ptr <Action> a = b2.createActionAttack (b1);
	a->apply ();

	EXPECT_EQ (b1.strength (), 95U);
	EXPECT_EQ (b2.strength (), 0U);
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
