#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, create) 
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 100, 100, 200, 300, 400};

	ASSERT_EQ (b1.name (), "mark");
	ASSERT_EQ (b1.x (), 10.1);
	ASSERT_EQ (b1.y (), 20.2);
	ASSERT_EQ (b1.speed (), 100);
	ASSERT_EQ (b1.smell (), 200);
	ASSERT_EQ (b1.strength (), 300);
	ASSERT_EQ (b1.endurance (), 400);
	ASSERT_EQ (b1.fatigue(), 0);

	ASSERT_FALSE (b1.isDead ());
	ASSERT_FALSE (b1.isTired ());

	Blob b2 {"annette", [](double) {return 0;}, -10.1, -20.2, 300, 300, 400, 500, 600};

	ASSERT_EQ (b2.name (), "annette");
	ASSERT_EQ (b2.x (), -10.1);
	ASSERT_EQ (b2.y (), -20.2);
	ASSERT_EQ (b2.speed (), 300);
	ASSERT_EQ (b2.smell (), 400);
	ASSERT_EQ (b2.strength (), 500);
	ASSERT_EQ (b2.endurance (), 600);
	ASSERT_EQ (b2.fatigue(), 0);

	ASSERT_FALSE (b2.isDead ());
	ASSERT_FALSE (b2.isTired ());
}

TEST (Blob, parms)
{
	Blob b {"mark", [](double) {return 0;}, 20, 40, 5, 10, 100, 22};
	std::shared_ptr<Action> a (new Movement (&b, "", 10.0, M_PI / 2));
	a->apply ();

	ASSERT_EQ (b.parms (), "alive,5,10,100,22,90");
}

TEST (Blob, output)
{
	Blob b {"mark", [](double) {return 0;}, 20, 40, 5, 5, 100, 0};
	std::shared_ptr<Action> a (new Movement (&b, "", 10.0, M_PI / 2));
	a->apply ();

	std::stringstream s;

	s << b;

	ASSERT_EQ (s.str (), "30,40");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
