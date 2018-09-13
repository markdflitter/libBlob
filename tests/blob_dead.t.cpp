#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, dead_blobs_do_nothing)
{
	std::vector<Blob> blobs {Blob ()};

	std::shared_ptr<Action> a1 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a1));
	std::shared_ptr <Movement> m1 (std::dynamic_pointer_cast <Movement> (a1));
	EXPECT_EQ (*m1, Movement (&blobs[0],"wandering", 0.0, 0.0));

	blobs[0].kill ();
	
	std::shared_ptr<Action> a2 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a2));
	std::shared_ptr <Movement> m2 (std::dynamic_pointer_cast <Movement> (a2));
	EXPECT_EQ (*m2, Movement (&blobs[0],"dead",0,0));
}

TEST (Blob, does_not_hunt_dead_blobs)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 5.0, 5.0, 100U),
		Blob ("", [](double) {return 0.0;}, 10.0, 12.0, 5.0, 5.0, 100, 0)};
	
	std::shared_ptr<Action> a1 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a1));
	std::shared_ptr <Movement> m1 (std::dynamic_pointer_cast <Movement> (a1));
	EXPECT_EQ (*m1, Movement (&blobs[0],"hunting  (fast)", 2.0, 0.0));

	blobs[1].kill ();

	std::shared_ptr<Action> a2 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a2));
	std::shared_ptr <Movement> m2 (std::dynamic_pointer_cast <Movement> (a2));
	EXPECT_EQ (m2->_reason, "wandering");
}

TEST (Blob, does_not_flee_dead_blobs)
{
	std::vector<Blob> blobs {	
		Blob ("", [](double) {return 0.0;}, 5.0, 5.0, 2.0, 4.0, 1.0, 0U, 0U, 0.0),
		Blob ("", [](double) {return 0.0;}, 5.0, 4.5, 12.0, 12.0, 1.0, 10U)};

	std::shared_ptr<Action> a1 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a1));
	std::shared_ptr <Movement> m1 (std::dynamic_pointer_cast <Movement> (a1));
	EXPECT_EQ (*m1, Movement (&blobs[0], "running from  (fast)", 4.0, 0.0));
	
	blobs[1].kill ();

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (m->_reason, "wandering");
}

TEST (Blob, does_not_attack_dead_blobs)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 5.0, 0.0, 10U),
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 5.0, 0.0, 0U)};

	std::shared_ptr<Action> a1 = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Attack> (a1));
	std::shared_ptr <Attack> atk1 (std::dynamic_pointer_cast <Attack> (a1));
	EXPECT_EQ (*atk1, Attack (&blobs[1], &blobs[0]));

	blobs[1].kill ();
	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (m->_reason, "wandering");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

