#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, blob_history)
{
	Blob b1 ("", [](double) {return 0;}, 10, 20);
	b1.move (5, M_PI, "");
	b1.move (5, M_PI, "");
	b1.move (5, M_PI / 2, "");

	std::vector<Pt<double>> history = b1.history ();
	ASSERT_TRUE (history.size () == 4);
	ASSERT_TRUE (history[0].x () == 10);
 	ASSERT_TRUE (history[0].y () == 20);
	ASSERT_TRUE (history[1].x () == 10);
 	ASSERT_TRUE (history[1].y () == 15);
	ASSERT_TRUE (history[2].x () == 10);
 	ASSERT_TRUE (history[2].y () == 10);
	ASSERT_TRUE (history[3].x () == 15);
 	ASSERT_TRUE (history[3].y () == 10);
}

TEST (Blob, blob_history_length)
{
	Blob b1 ("", [](double) {return 0;}, 10, 20);
	for (int i = 0; i < 1000; i++)
	{
		b1.move (5, 0, "");
	}
	
	std::vector<Pt<double>> history = b1.history ();
	ASSERT_TRUE (history.size () == 500);
	
	ASSERT_TRUE (history[0].x () == 10);
 	ASSERT_TRUE (history[0].y () == 2525);
	
	ASSERT_TRUE (history[499].x () == 10);
 	ASSERT_TRUE (history[499].y () == 5020);
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

