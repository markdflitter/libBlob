#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, fight_without_killing)
{
	Blob b1 ("", [](double) {return 0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 100U);
	EXPECT_EQ (b1.strength (), 100U);
	
	b1.takeDamage (10U);
	EXPECT_EQ (b1.strength (), 90U);
	EXPECT_FALSE (b1.isDead ());
}

TEST (Blob, fight_and_kill)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 20U);
	EXPECT_EQ (b1.strength (), 20U);
		
	b1.takeDamage (10U);
	EXPECT_EQ (b1.strength (), 10U);
	EXPECT_FALSE (b1.isDead ());
	
	b1.takeDamage (10U);
	EXPECT_EQ (b1.strength (), 0U);
	EXPECT_TRUE (b1.isDead ());
}

TEST (Blob, fight_and_overkill)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 0.0, 0.0, 0.0, 20U);
	EXPECT_EQ (b1.strength (), 20U);
		
	b1.takeDamage (100U);
	EXPECT_EQ (b1.strength (), 0U);
	EXPECT_TRUE (b1.isDead ());
}

TEST (Blob, chooses_not_to_fight_because_in_different_squares)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (m->_reason, "wandering");
}

TEST (Blob, will_not_fight_self)
{
	std::vector <Blob> blobs {Blob ()};
	
	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (m->_reason, "wandering");
}

TEST (Blob, will_not_fight_stronger_unless_aggressive)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 0U, 0U, 0.4),
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 100U)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	ASSERT_EQ (m->_reason, "running from  (fast)");
}

TEST (Blob, chooses_to_fight)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 10U),
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 2U)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Fight> (a));
	std::shared_ptr <Fight> m (std::dynamic_pointer_cast <Fight> (a));
	
	EXPECT_EQ (m->_target,  &blobs[1]);
	EXPECT_EQ (m->_attacker, &blobs[0]);
}

TEST (Blob, chooses_to_fight_weakest)
{
	std::vector <Blob> blobs {	
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 10U),
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 2U),
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 3U)};
		
	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Fight> (a));
	std::shared_ptr <Fight> m (std::dynamic_pointer_cast <Fight> (a));

	EXPECT_EQ (m->_target, &blobs[1]);
	EXPECT_EQ (m->_attacker, &blobs[0]);
}

TEST (Blob, actually_fights_and_kills)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 10U),
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 0.0, 0.0, 0.0, 2U)};

	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Action> a = blobs.front ().chooseNextAction (blobs); 
		a->apply ();
	}
	
	ASSERT_TRUE (blobs[1].isDead ());
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

