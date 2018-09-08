#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, dead_blobs_do_nothing)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 100, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 5, 5, 100, 100};
	std::vector <Blob> blobs {b1, b2};
	
	blobs[0].kill ();
	
	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&blobs[0],"dead",0,0));
}

TEST (Blob, dead_blobs_are_not_hunted)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 100, 0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 5, 5, 100, 100};
	std::vector <Blob> blobs {b1, b2};
	
	blobs[0].kill ();

	std::shared_ptr<Action> a = blobs[1].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, does_not_run_from_dead_blobs)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 2, 2, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 5, 5, 12, 12, 0, 10};
	std::vector<Blob> blobs {b1,b2};
	
	blobs[1].kill ();

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, chooses_not_to_fight_dead)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 5, 5, 0, 0};
	std::vector <Blob> blobs {b1, b2};
	
	blobs.back().kill ();
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "wandering");
}int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

