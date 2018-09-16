#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, hunts_north)
{
	Blob b1 ("", [](double) {return 0.0;}, 5.0, 5.0, 2.0, 4.0);
	Blob b2 ("", [](double) {return 0.0;}, 5.0, 10.0, 12.0, 12.0);

	std::shared_ptr<Action> a = b1.createActionHunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&b1, "hunting  (fast)", 4, 0));

	a->apply ();
	EXPECT_DOUBLE_EQ (b1.y (), 9.0);
}

TEST (Blob, hunt_south)
{
	Blob b1 ("", [](double) {return 0.0;}, 5.0, 5.0, 2.0, 4.0);
	Blob b2 ("", [](double) {return 0.0;}, 5.0, -10.0, 12.0, 12.0);

	std::shared_ptr<Action> a = b1.createActionHunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&b1, "hunting  (fast)", 4, M_PI));

	a->apply ();
	EXPECT_DOUBLE_EQ (b1.y (), 1.0);
}

TEST (Blob, hunt_east)
{
	Blob b1 ("", [](double) {return 0.0;}, 5.0, 5.0, 2.0, 4.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 5.0, 12.0, 12.0);

	std::shared_ptr<Action> a = b1.createActionHunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&b1, "hunting  (fast)", 4, M_PI/2));

	a->apply ();
	EXPECT_DOUBLE_EQ (b1.x (), 9.0);
}

TEST (Blob, hunt_west)
{
	Blob b1 ("", [](double) {return 0.0;}, -5.0, 5.0, 2.0, 4.0);
	Blob b2 ("", [](double) {return 0.0;}, -10.0, 5.0, 12.0, 12.0);

	std::shared_ptr<Action> a = b1.createActionHunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&b1, "hunting  (fast)", 4, 3 * M_PI / 2));

	a->apply ();
	EXPECT_DOUBLE_EQ (b1.x (), -9.0);
}

TEST (Blob, hunt_get_closer)
{
	Blob b1 ("", [](double) {return 0.0;}, -5.0, 5.0, 7.0, 7.0);
	Blob b2 ("", [](double) {return 0.0;}, -10.0, 5.0, 12.0, 12.0);

	double d1 = b1.distance (b2);
	std::shared_ptr<Action> m = b1.createActionHunt (b2);
	m->apply ();

	double d2 = b1.distance (b2);
	EXPECT_LT (d2, d1);
}

TEST (Blob, hunt_catches)
{
	Blob b1 ("", [](double) {return 0.0;}, -5.0, 5.0, 7.0, 7.0);
	Blob b2 ("", [](double) {return 0.0;}, -10.0, 5.0, 12.0, 12.0);

	std::shared_ptr<Action> a = b1.createActionHunt (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr<Movement> m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_LT (m->_speed, 7.0);
	a->apply ();

	EXPECT_TRUE (b1.isInSameSquare (b2));
}

TEST (Blob, chooses_to_hunt)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 10.0, 100.0, 1U),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0, 5.0, 5.0, 100.0)};

	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&blobs[0], "hunting  (fast)", 10, M_PI/4)); 
}

TEST (Blob, chooses_not_to_hunt_because_not_aggressive)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 10.0, 1000.0, 1U, 0U, 0.0),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0, 5.0, 5.0, 1000.0, 0U)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (m->_reason, "running from  (fast)");
}

TEST (Blob, chooses_not_to_hunt_because_weaker)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 10.0, 1000.0, 0U, 0U, 0.0),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0, 5.0, 5.0, 1000.0, 1U)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (m->_reason, "running from  (fast)");
}


TEST (Blob, chooses_closest_to_hunt)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 10.0, 1000.0, 1U),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0, 5.0, 5.0, 1000.0, 0U),
		Blob ("", [](double) {return 0.0;}, 25.0, 25.0, 5.0, 5.0, 1000.0, 0U)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (*m, Movement (&blobs[0], "hunting  (fast)", 10, M_PI/4)); 
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

