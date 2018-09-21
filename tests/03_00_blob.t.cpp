#include <gtest/gtest.h>
#include <blob.h>

TEST (test_03_00_blob_t, create_default_blob)
{
	Blob b = CreateBlob ();
}

TEST (test_03_00_blob_t, name)
{
	Blob mark = CreateBlob ().name("mark");
	EXPECT_EQ (mark.name (), "mark");
}

TEST (test_03_00_blob_t, position)
{
	Blob b = CreateBlob ().position (make_pt (100.1, 200.2));
	EXPECT_DOUBLE_EQ (b.x (), 100.1);
	EXPECT_DOUBLE_EQ (b.y (), 200.2);
}

TEST (test_03_00_blob_t, speed)
{
	Blob b = CreateBlob ().speed (300.3);
	EXPECT_DOUBLE_EQ (b.speed (), 300.3);
}

TEST (test_03_00_blob_t, running_speed)
{
	Blob b = CreateBlob ().runningSpeed (400.4);
	EXPECT_DOUBLE_EQ (b.runningSpeed (), 400.4);
}

TEST (test_03_00_blob_t, HP)
{
	Blob b = CreateBlob ().HP (500U);
	EXPECT_EQ (b.maxHP (), 500U);
	EXPECT_EQ (b.HP (), 500U);
}

TEST (test_03_00_blob_t, endurance)
{
	Blob b = CreateBlob ().endurance(600U);
	EXPECT_EQ (b.endurance (), 600U);
}

TEST (test_03_00_blob_t, aggression)
{
	Blob b = CreateBlob ().aggression (700.7);
	EXPECT_DOUBLE_EQ (b.aggression (), 700.7);
}

TEST (test_03_00_blob_t, lifespan)
{
	Blob b = CreateBlob().lifespan (800U);
	EXPECT_EQ (b.lifespan (), 800U);
}

TEST (test_03_00_blob_t, age)
{
	Blob b = CreateBlob ();
	EXPECT_EQ (b.age (), 0U);
}

TEST (test_03_00_blob_t, state)
{
	Blob b = CreateBlob ();
	EXPECT_EQ (b.state (), "newborn");
}

TEST (test_03_00_blob_t, fatigue)
{
	Blob b = CreateBlob ();
	EXPECT_EQ (b.fatigue (), 0U);
}

TEST (test_03_00_blob_t, starts_untired)
{
	Blob b = CreateBlob ();
	EXPECT_FALSE (b.isTired ());
}

TEST (test_03_00_blob_t, starts_alive)
{
	Blob b = CreateBlob ();
	EXPECT_FALSE (b.isDead ());
}

TEST (test_03_00_blob_t, output)
{
	Blob b = CreateBlob ().position (make_pt (20.2, 40.4));
	
	std::stringstream s;

	s << b;

	EXPECT_EQ (s.str (), "20.2,40.4");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
