#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, choosesToHunt)
{
	Blob b1 {"mark", [](double) {return 0;}, 10.0, 10.0, 5.0, 10.0, 100.0, 1, 1};
	Blob b2 {"annette", [](double) {return 0;}, 20, 20, 5, 5, 100, 0};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (*m == Movement (&blobs.front (), "hunting annette (fast)", 10, M_PI/4)); 
}


TEST (Blob, choosesClosestToHunt)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 10, 1000, 1, 1};
	Blob b2 {"annette", [](double) {return 0;}, 20, 20, 5, 5, 1000, 0};
	Blob b3 {"duncan", [](double) {return 0;}, 25, 25, 5, 5, 1000, 0};
	std::vector <Blob> blobs {b1, b2, b3};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (*m == Movement (&blobs.front (), "hunting annette (fast)", 10, M_PI/4)); 
}

TEST (Blob, chooses_not_to_fight)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 20, 20, 5, 5, 0, 0};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, will_not_fight_self)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 1000, 0};
	std::vector <Blob> blobs {b1};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "wandering");
}

TEST (Blob, will_not_fight_stronger)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 1, 0, 0, 0.0};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 5, 5, 0, 100};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "running from annette (fast)");
}

TEST (Blob, chooses_to_fight)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 5, 5, 0, 2};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Attack> (a));
	std::shared_ptr <Attack> m (std::dynamic_pointer_cast <Attack> (a));
	
	ASSERT_TRUE (m->_target == &blobs[1]);
	ASSERT_TRUE (m->_strength == 10);
}

TEST (Blob, chooses_to_fight_weakest)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 5, 5, 0, 2};
	Blob b3 {"duncan", [](double) {return 0;}, 10, 10, 5, 5, 0, 3};
	std::vector <Blob> blobs {b1, b2, b3};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Attack> (a));
	std::shared_ptr <Attack> m (std::dynamic_pointer_cast <Attack> (a));
	
	ASSERT_TRUE (m->_target == &blobs[1]);
	ASSERT_TRUE (m->_strength == 10);
}


TEST (Blob, actually_fights_and_kills)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 0, 10};
	Blob b2 {"annette", [](double) {return 0;}, 10, 10, 5, 5, 0, 2};
	std::vector <Blob> blobs {b1, b2};
	
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
		a->apply ();
	}
	ASSERT_TRUE (blobs[1].isDead ());
}


TEST (Blob, runs)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 1000, 0, 0, 0.5};
	Blob b2 {"annette", [](double) {return 0;}, 20, 20, 5, 5,0, 1};
	std::vector <Blob> blobs {b1, b2};
	
	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "running from annette (fast)");
}

TEST (Blob, runs_from_strongest)
{
	Blob b1 {"mark", [](double) {return 0;}, 10, 10, 5, 5, 1000, 0, 0, 0.5};
	Blob b2 {"annette", [](double) {return 0;}, 20, 20, 5, 5, 0, 1};
	Blob b3 {"duncan", [](double) {return 0;}, 20, 20, 5, 5, 0, 2};
	std::vector <Blob> blobs {b1, b2, b3};

	std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_TRUE (m->_reason == "running from duncan (fast)");
}

TEST (Blob, does_not_run)
{
	Blob b1 {"mark", [](double) {return 0;}, 5, 5, 2, 2, 0, 0};
	Blob b2 {"annette", [](double) {return 0;}, 5, 10, 12, 12, 0, 0};
	std::vector<Blob> blobs {b1,b2};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_TRUE (m->_reason == "wandering");
}


int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

