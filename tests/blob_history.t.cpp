#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, history)
{
	Blob b1 ("", [](double) {return 0;}, 10.0, 20.0);
	b1.move (5.0, M_PI, "");
	b1.move (5.0, M_PI, "");
	b1.move (5.0, M_PI / 2, "");

	std::vector<Pt<double>> history = b1.history ();
	ASSERT_EQ (history.size (), 4);
	ASSERT_EQ (history[0].x (), 10.0);
 	ASSERT_EQ (history[0].y (), 20.0);
	ASSERT_EQ (history[1].x (), 10.0);
 	ASSERT_EQ (history[1].y (), 15.0);
	ASSERT_EQ (history[2].x (), 10.0);
 	ASSERT_EQ (history[2].y (), 10.0);
	ASSERT_EQ (history[3].x (), 15.0);
 	ASSERT_EQ (history[3].y (), 10.0);
}

TEST (Blob, history_length)
{
	Blob b1 ("", [](double) {return 0;}, 10.0, 20.0);
	for (int i = 0; i < 1000; i++)
	{
		b1.move (5.0, 0, "");
	}
	
	std::vector<Pt<double>> history = b1.history ();
	ASSERT_EQ (history.size (), 500);
	
	ASSERT_EQ (history[0].x (), 10.0);
 	ASSERT_EQ (history[0].y (), 2525);
	
	ASSERT_EQ (history[499].x (), 10.0);
 	ASSERT_EQ (history[499].y (), 5020);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
