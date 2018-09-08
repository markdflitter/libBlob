#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, do_not_move)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	b1.move (0.0, 0.0, "");
	
	ASSERT_DOUBLE_EQ (b1.x (), 0.0);
	ASSERT_DOUBLE_EQ (b1.y (), 0.0);
}

TEST (Blob, move_north)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 15.2);
	b1.move (5.0, 0.0, "move north");

	ASSERT_DOUBLE_EQ (b1.x (), 10.1);
	ASSERT_DOUBLE_EQ (b1.y (), 20.2);
	ASSERT_EQ (b1.state (), "move north");
}

TEST (Blob, move_south)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, M_PI, "move south");

	ASSERT_DOUBLE_EQ (b1.x (), 10.1);
	ASSERT_DOUBLE_EQ (b1.y (), 15.2);
	ASSERT_EQ (b1.state (), "move south");
}

TEST (Blob, move_minus_south)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -M_PI, "move south");

	ASSERT_DOUBLE_EQ (b1.x (), 10.1);
	ASSERT_DOUBLE_EQ (b1.y (), 15.2);
	ASSERT_EQ (b1.state (), "move south");
}


TEST (Blob, move_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, M_PI / 2.0, "move east");

	ASSERT_DOUBLE_EQ (b1.x (), 15.1);
	ASSERT_DOUBLE_EQ (b1.y (), 20.2);
	ASSERT_EQ (b1.state (), "move east");
}

TEST (Blob, move_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, 3.0 * M_PI / 2.0, "move west");

	ASSERT_DOUBLE_EQ (b1.x (), 5.1);
	ASSERT_DOUBLE_EQ (b1.y (), 20.2);
	ASSERT_EQ (b1.state (), "move west");
}

TEST (Blob, move_minus_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -M_PI / 2.0, "move west");

	ASSERT_DOUBLE_EQ (b1.x (), 5.1);
	ASSERT_DOUBLE_EQ (b1.y (), 20.2);
	ASSERT_EQ (b1.state (), "move west");
}

TEST (Blob, move_north_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, M_PI / 4.0, "move north east");

	ASSERT_DOUBLE_EQ (b1.x (), 13.63553390593273);
	ASSERT_DOUBLE_EQ (b1.y (), 23.735533905932737);
	ASSERT_EQ (b1.state (), "move north east");
}

TEST (Blob, move_north_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -M_PI / 4.0, "move north west");

	ASSERT_DOUBLE_EQ (b1.x (), 06.564466094067262);
	ASSERT_DOUBLE_EQ (b1.y (), 23.735533905932737);
	ASSERT_EQ (b1.state (), "move north west");

	Blob b2 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b2.move (5.0, 7.0 * M_PI / 4.0, "move north west");
	
	ASSERT_DOUBLE_EQ (b2.x (), 06.56446609406726);
	ASSERT_DOUBLE_EQ (b2.y (), 23.73553390593273);
	ASSERT_EQ (b1.state (), "move north west");
}

TEST (Blob, move_south_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, 3.0 * M_PI / 4.0, "move south east");

	ASSERT_DOUBLE_EQ (b1.x (), 13.63553390593273);
	ASSERT_DOUBLE_EQ (b1.y (), 16.66446609406726);
	ASSERT_EQ (b1.state (), "move south east");
}

TEST (Blob, move_south_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, 5.0 * M_PI / 4.0, "move south west");

	ASSERT_DOUBLE_EQ (b1.x (), 06.56446609406726);
	ASSERT_DOUBLE_EQ (b1.y (), 16.66446609406726);
	ASSERT_EQ (b1.state (), "move south west");
}

TEST (Blob, move_minus_south_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -3.0 * M_PI / 4.0, "move south west");

	ASSERT_DOUBLE_EQ (b1.x (), 06.56446609406726);
	ASSERT_DOUBLE_EQ (b1.y (), 16.66446609406726);
	ASSERT_EQ (b1.state (), "move south west");
}

TEST (Blob, move_negative_x)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (20.0, 3.0 * M_PI / 2.0, "-x");

	ASSERT_DOUBLE_EQ (b1.x (), -9.9);
	ASSERT_DOUBLE_EQ (b1.y (), 20.2);
	ASSERT_EQ (b1.state (), "-x");
}

TEST (Blob, move_negative_y)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (30.0, M_PI, "-y");

	ASSERT_DOUBLE_EQ (b1.x (), 10.1);
	ASSERT_DOUBLE_EQ (b1.y (), -9.8);
	ASSERT_EQ (b1.state (), "-y");
}

TEST (Blob, moveFast)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (10.0, 0.0, "move fast");

	ASSERT_DOUBLE_EQ (b1.x (), 10.1);
	ASSERT_DOUBLE_EQ (b1.y (), 30.2);
	ASSERT_EQ (b1.state (), "move fast");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

