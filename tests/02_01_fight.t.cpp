#include <fight.h>
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

	void takeDamage (unsigned int damage)
	{
		_damageTaken = damage;
	}

	unsigned int _damageTaken = 0;
	unsigned int _damage = 0;
};

TEST(test_02_01_fight_t, create)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a (&tm1, &tm2);
	EXPECT_EQ (a._target, &tm1);
	EXPECT_EQ (a._attacker, &tm2);
}

TEST(test_02_01_fight_t, equal_to_self)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a (&tm1, &tm2);
	EXPECT_TRUE (a == a);
}

TEST (test_02_01_fight_t, equal_to_other)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a1 (&tm1, &tm2);
	Fight a2 (&tm1, &tm2);
	EXPECT_TRUE (a1 == a2);
}

TEST (test_02_01_fight_t, equal_false_different_target)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a1 (&tm1, &tm2);
	Fight a2 (&tm2, &tm2);
	EXPECT_FALSE (a1 == a2);
}

TEST (test_02_01_fight_t, equal_false_different_attacker)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a1 (&tm1, &tm2);
	Fight a2 (&tm1, &tm1);
	EXPECT_FALSE (a1 == a2);
}

TEST(test_02_01_fight_t, not_equal_equal_to_self)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a (&tm1, &tm2);
	EXPECT_FALSE (a != a);
}

TEST(test_02_01_fight_t, not_equal_different_target)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a1 (&tm1, &tm2);
	Fight a2 (&tm2, &tm2);
	EXPECT_TRUE (a1 != a2);
}

TEST(test_02_01_fight_t, not_equal_different_attacker)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	Fight a1 (&tm1, &tm2);
	Fight a2 (&tm1, &tm1);
	EXPECT_TRUE (a1 != a2);
}

TEST (test_02_01_fight_t, output)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	std::shared_ptr<Action> a (new Fight (&tm1, &tm2));
	EXPECT_TRUE (std::dynamic_pointer_cast <Fight> (a));
	std::shared_ptr <Fight> m (std::dynamic_pointer_cast <Fight> (a));
	
	std::stringstream s;

	s << *m;

	EXPECT_EQ (s.str (), "20");
}

TEST (test_02_01_fight_t, apply_target_is_damaged)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	std::shared_ptr<Action> a (new Fight (&tm1, &tm2));
	
	a->apply ();
	EXPECT_EQ (tm1._damageTaken, 20U);
}

TEST (test_02_01_fight_t, apply_attacker_is_damaged)
{
	TargetMock tm1 (10U);
	TargetMock tm2 (20U);
	std::shared_ptr<Action> a (new Fight (&tm1, &tm2));
	
	a->apply ();
	EXPECT_EQ (tm2._damageTaken, 10U);
}

TEST (test_02_01_fight_t, applies_to_blobs)
{
	Blob target = CreateBlob ().HP (7U).damage (1U);
	Blob attacker = CreateBlob ().HP (6U).damage (5U);

	std::shared_ptr <Action> a = attacker.createActionFight (target);
	a->apply ();

	EXPECT_EQ (target.HP (), 2U);
	EXPECT_EQ (attacker.HP (), 5U);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
