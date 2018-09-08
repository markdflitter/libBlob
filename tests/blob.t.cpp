#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, createDefaultBlob)
{
	Blob b;
}


TEST (Blob, name)
{
	Blob b("mark");
	ASSERT_EQ (b.name (), "mark");
}

TEST (Blob, x)
{
	Blob b("", [](double) {return 0.0;}, 100.1);
	ASSERT_EQ (b.x (), 100.1);
}

TEST (Blob, y)
{
	Blob b("", [](double) {return 0.0;}, 0.0, 200.2);
	ASSERT_EQ (b.y (), 200.2);
}

TEST (Blob, speed)
{
	Blob b ("", [](double) {return 0.0;}, 0.0, 0.0, 300.3);
	ASSERT_EQ (b.speed (), 300.3);
}

TEST (Blob, running_speed)
{
	Blob b ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 400.4);
	ASSERT_EQ (b.runningSpeed (), 400.4);
}

TEST (Blob, strength)
{
	Blob b ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 500.5);
	ASSERT_EQ (b.strength (), 500.5);
}

TEST (Blob, endurance)
{
	Blob b ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 600);
	ASSERT_EQ (b.endurance (), 600);
}

TEST (Blob, aggression)
{
	Blob b ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 700.7);
	ASSERT_EQ (b.aggression (), 700.7);
}

TEST (Blob, state)
{
	Blob b;
	ASSERT_EQ (b.state (), "newborn");
}

TEST (Blob, fatigue)
{
	Blob b;
	ASSERT_EQ (b.fatigue (), 0.0);
}

TEST (Blob, starts_untired)
{
	Blob b;
	ASSERT_FALSE (b.isTired ());
}

TEST (Blob, starts_alive)
{
	Blob b;
	ASSERT_FALSE (b.isDead ());
}

TEST (Blob, output)
{
	Blob b ("", [](double) {return 0.0;}, 20.2, 40.4);
	
	std::stringstream s;

	s << b;

	ASSERT_EQ (s.str (), "20.2,40.4");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
