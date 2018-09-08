#include <gtest/gtest.h>
#include <blob.h>

constexpr double threshold = 0.00001;

TEST (Blob, moveN)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 15.2, 5, 5, 0, 0};
	b1.move (5, 0, "N");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "N");
}

TEST (Blob, moveFast)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (10, 0, "N");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 30.2) < threshold);
	ASSERT_TRUE (b1.state () == "N");
}

TEST (Blob, moveS)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, M_PI, "S");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 15.2) < threshold);
	ASSERT_TRUE (b1.state () == "S");

	b1.move (5, -M_PI, "S");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 10.2) < threshold);
	ASSERT_TRUE (b1.state () == "S");
}


TEST (Blob, moveE)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, M_PI / 2, "E");

	ASSERT_TRUE (fabs (b1.x () - 15.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "E");
}

TEST (Blob, moveW)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, 3 * M_PI / 2, "W");

	ASSERT_TRUE (fabs (b1.x () - 5.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "W");

	b1.move (5, -M_PI / 2, "W");

	ASSERT_TRUE (fabs (b1.x () - 0.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "W");
}

TEST (Blob, moveNE)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, M_PI / 4,"NE");

	ASSERT_TRUE (fabs (b1.x () - 13.635533905932737) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 23.735533905932737) < threshold);
	ASSERT_TRUE (b1.state () == "NE");
}

TEST (Blob, moveNW)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, -M_PI / 4, "NW");

	ASSERT_TRUE (fabs (b1.x () - 06.564466094067262) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 23.735533905932737) < threshold);
	ASSERT_TRUE (b1.state () == "NW");

	Blob b2 {"annette", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b2.move (5, 7 * M_PI / 4, "NW");
	
	ASSERT_TRUE (fabs (b2.x () - 06.56446609406726) < threshold);
	ASSERT_TRUE (fabs (b2.y () - 23.73553390593273) < threshold);
	ASSERT_TRUE (b1.state () == "NW");
}

TEST (Blob, moveSE)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, 3 * M_PI / 4, "SE");

	ASSERT_TRUE (fabs (b1.x () - 13.63553390593273) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 16.66446609406726) < threshold);
	ASSERT_TRUE (b1.state () == "SE");
}

TEST (Blob, moveSW)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (5, 5 * M_PI / 4, "SW");

	ASSERT_TRUE (fabs (b1.x () - 06.56446609406726) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 16.66446609406726) < threshold);
	ASSERT_TRUE (b1.state () == "SW");

	Blob b2 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b2.move (5, -3 * M_PI / 4, "SW");

	ASSERT_TRUE (fabs (b2.x () - 06.56446609406726) < threshold);
	ASSERT_TRUE (fabs (b2.y () - 16.66446609406726) < threshold);
	ASSERT_TRUE (b1.state () == "SW");
}

TEST (Blob, moveNegativeX)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (20, 3 * M_PI / 2, "-x");

	ASSERT_TRUE (fabs (b1.x () - -9.9) < threshold);
	ASSERT_TRUE (fabs (b1.y () - 20.2) < threshold);
	ASSERT_TRUE (b1.state () == "-x");
}

TEST (Blob, moveNegativeY)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	b1.move (30, M_PI, "-y");

	ASSERT_TRUE (fabs (b1.x () - 10.1) < threshold);
	ASSERT_TRUE (fabs (b1.y () - -9.8) < threshold);
	ASSERT_TRUE (b1.state () == "-y");
}

TEST (Blob, movement)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.1, 20.2, 5, 5, 0, 0};
	std::shared_ptr<Action> m (new Movement (&b1, "because", 5.0, 0.0));
        m->apply ();
	
	ASSERT_EQ (b1.x (), 10.1);
	ASSERT_EQ (b1.y (), 25.2);
	ASSERT_TRUE (b1.state () == "because");
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

