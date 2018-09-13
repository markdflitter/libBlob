#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, do_not_move)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0);
	b1.move (0.0, 0.0, "");
	
	EXPECT_DOUBLE_EQ (b1.x (), 0.0);
	EXPECT_DOUBLE_EQ (b1.y (), 0.0);
}

TEST (Blob, move_north)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 15.2);
	b1.move (5.0, 0.0, "move north");

	EXPECT_DOUBLE_EQ (b1.x (), 10.1);
	EXPECT_DOUBLE_EQ (b1.y (), 20.2);
	EXPECT_EQ (b1.state (), "move north");
}

TEST (Blob, move_south)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, M_PI, "move south");

	EXPECT_DOUBLE_EQ (b1.x (), 10.1);
	EXPECT_DOUBLE_EQ (b1.y (), 15.2);
	EXPECT_EQ (b1.state (), "move south");
}

TEST (Blob, move_minus_south)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -M_PI, "move south");

	EXPECT_DOUBLE_EQ (b1.x (), 10.1);
	EXPECT_DOUBLE_EQ (b1.y (), 15.2);
	EXPECT_EQ (b1.state (), "move south");
}


TEST (Blob, move_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, M_PI / 2.0, "move east");

	EXPECT_DOUBLE_EQ (b1.x (), 15.1);
	EXPECT_DOUBLE_EQ (b1.y (), 20.2);
	EXPECT_EQ (b1.state (), "move east");
}

TEST (Blob, move_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, 3.0 * M_PI / 2.0, "move west");

	EXPECT_DOUBLE_EQ (b1.x (), 5.1);
	EXPECT_DOUBLE_EQ (b1.y (), 20.2);
	EXPECT_EQ (b1.state (), "move west");
}

TEST (Blob, move_minus_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -M_PI / 2.0, "move west");

	EXPECT_DOUBLE_EQ (b1.x (), 5.1);
	EXPECT_DOUBLE_EQ (b1.y (), 20.2);
	EXPECT_EQ (b1.state (), "move west");
}

TEST (Blob, move_north_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, M_PI / 4.0, "move north east");

	EXPECT_DOUBLE_EQ (b1.x (), 13.63553390593273);
	EXPECT_DOUBLE_EQ (b1.y (), 23.735533905932737);
	EXPECT_EQ (b1.state (), "move north east");
}

TEST (Blob, move_north_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -M_PI / 4.0, "move north west");

	EXPECT_DOUBLE_EQ (b1.x (), 06.564466094067262);
	EXPECT_DOUBLE_EQ (b1.y (), 23.735533905932737);
	EXPECT_EQ (b1.state (), "move north west");

	Blob b2 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b2.move (5.0, 7.0 * M_PI / 4.0, "move north west");
	
	EXPECT_DOUBLE_EQ (b2.x (), 06.56446609406726);
	EXPECT_DOUBLE_EQ (b2.y (), 23.73553390593273);
	EXPECT_EQ (b1.state (), "move north west");
}

TEST (Blob, move_south_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, 3.0 * M_PI / 4.0, "move south east");

	EXPECT_DOUBLE_EQ (b1.x (), 13.63553390593273);
	EXPECT_DOUBLE_EQ (b1.y (), 16.66446609406726);
	EXPECT_EQ (b1.state (), "move south east");
}

TEST (Blob, move_south_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, 5.0 * M_PI / 4.0, "move south west");

	EXPECT_DOUBLE_EQ (b1.x (), 06.56446609406726);
	EXPECT_DOUBLE_EQ (b1.y (), 16.66446609406726);
	EXPECT_EQ (b1.state (), "move south west");
}

TEST (Blob, move_minus_south_west)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (5.0, -3.0 * M_PI / 4.0, "move south west");

	EXPECT_DOUBLE_EQ (b1.x (), 06.56446609406726);
	EXPECT_DOUBLE_EQ (b1.y (), 16.66446609406726);
	EXPECT_EQ (b1.state (), "move south west");
}

TEST (Blob, move_negative_x)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (20.0, 3.0 * M_PI / 2.0, "-x");

	EXPECT_DOUBLE_EQ (b1.x (), -9.9);
	EXPECT_DOUBLE_EQ (b1.y (), 20.2);
	EXPECT_EQ (b1.state (), "-x");
}

TEST (Blob, move_negative_y)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (30.0, M_PI, "-y");

	EXPECT_DOUBLE_EQ (b1.x (), 10.1);
	EXPECT_DOUBLE_EQ (b1.y (), -9.8);
	EXPECT_EQ (b1.state (), "-y");
}

TEST (Blob, move_fast)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.1, 20.2);
	b1.move (10.0, 0.0, "move fast");

	EXPECT_DOUBLE_EQ (b1.x (), 10.1);
	EXPECT_DOUBLE_EQ (b1.y (), 30.2);
	EXPECT_EQ (b1.state (), "move fast");
}

TEST (Blob, move_limit_minx)
{
	Blob b1 ("", [](double) {return 0.0;});
	b1.move (1200.0, 3.0 * M_PI / 2.0, "");

	EXPECT_DOUBLE_EQ (b1.x (), -1000.0);
}

TEST (Blob, move_limit_maxx)
{
	Blob b1 ("", [](double) {return 0.0;});
	b1.move (1200.0, M_PI / 2.0, "");

	EXPECT_DOUBLE_EQ (b1.x (), 1000.0);
}

TEST (Blob, move_limit_maxy)
{
	Blob b1 ("", [](double) {return 0.0;});
	b1.move (1200.0, 0.0, "");

	EXPECT_DOUBLE_EQ (b1.y (), 1000.0);
}

TEST (Blob, move_limit_miny)
{
	Blob b1 ("", [](double) {return 0.0;});
	b1.move (1200.0, M_PI, "");

	EXPECT_DOUBLE_EQ (b1.y (), -1000.0);
}



TEST (Blob, move_limit_mix)
{
	Blob b1 ("", [](double) {return 0.0;});
	b1.move (1200.0, 3.0 * M_PI / 2.0, "");

	EXPECT_DOUBLE_EQ (b1.x (), -1000.0);
}

TEST (Blob, move_strength_recovers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 1.0, 100.0, 100U);
	b1.attack (20U);

	EXPECT_EQ (b1.strength (), 80U);
	b1.move (0.0, 0.0, "");
	EXPECT_EQ (b1.strength (), 81U);
}



int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

