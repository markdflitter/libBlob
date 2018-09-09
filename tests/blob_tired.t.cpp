#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, gets_tired_when_hunting)
{
	Blob b1 {"mark", Rnd (1, 40), 0, 0, 10, 20, 10, 0, 2};
	Blob b2 {"annette", Rnd (1, 40), 100, 100, 10, 10, 10, 0};
	
	ASSERT_FALSE (b1.isTired ());

	std::shared_ptr<Action> a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_FALSE (b1.isTired ());
	ASSERT_EQ (m->_speed, 20);
	a->apply ();

	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_FALSE (b1.isTired ());
	ASSERT_EQ (m->_speed, 20);
	a->apply ();
	
	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (b1.isTired ());
	ASSERT_EQ (m->_speed, 10);
	a->apply ();

	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (b1.isTired ());
	ASSERT_EQ (m->_speed, 10);
	a->apply ();

	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_FALSE (b1.isTired ());
	ASSERT_EQ (m->_speed, 20);
	a->apply ();
}

TEST (Blob, gets_tired_when_fleeing)
{
	Blob b1 {"mark", Rnd (1, 40), 0, 0, 10, 20, 10, 0, 2};
	Blob b2 {"annette", Rnd (1, 40), 100, 100, 10, 10, 10, 0};
	
	ASSERT_FALSE (b1.isTired ());

	std::shared_ptr<Action> a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	ASSERT_FALSE (b1.isTired ());
	ASSERT_EQ (m->_speed, 20);
	a->apply ();

	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_FALSE (b1.isTired ());
	ASSERT_EQ (m->_speed, 20);
	a->apply ();
	
	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (b1.isTired ());
	ASSERT_EQ (m->_speed, 10);
	a->apply ();

	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_TRUE (b1.isTired ());
	ASSERT_EQ (m->_speed, 10);
	a->apply ();

	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	ASSERT_FALSE (b1.isTired ());
	ASSERT_EQ (m->_speed, 20);
	a->apply ();
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

