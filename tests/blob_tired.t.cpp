#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, gets_tired_when_hunting_and_recovers)
{
	Blob b1 ("", [](double) {return 0.0;}, -100.0, -100.0, 0.0, 1.0, 10.0, 0U, 2U);
	Blob b2;
	
	EXPECT_FALSE (b1.isTired ());

	std::shared_ptr<Action> a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_FALSE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 1.0);
	a->apply ();

	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 1.0);
	a->apply ();
	
	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 0.0);
	a->apply ();

	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 0.0);
	a->apply ();

	a = b1.createActionHunt (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 1.0);
	a->apply ();
}

TEST (Blob, gets_tired_when_fleeing_and_recovers)
{
	Blob b1 ("", [](double) {return 0.0;}, 0.0, 0.0, 10.0, 20.0, 10.0, 0U, 2U);
	Blob b2;
	
	EXPECT_FALSE (b1.isTired ());

	std::shared_ptr<Action> a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_FALSE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 20.0);
	a->apply ();

	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 20.0);
	a->apply ();
	
	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 10.0);
	a->apply ();

	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_TRUE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 10.0);
	a->apply ();

	a = b1.createActionFlee (b2);	
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	m = std::dynamic_pointer_cast <Movement> (a);
	EXPECT_FALSE (b1.isTired ());
	EXPECT_DOUBLE_EQ (m->_speed, 20.0);
	a->apply ();
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

