#include <gtest/gtest.h>
#include <blob.h>

TEST (Blob, flee)
{
	Blob b1 ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 13.0);
	Blob b2 ("", [](double) {return 0.0;}, 10.0, 15.0, 12.0, 12.0);

	std::shared_ptr<Action> a = b1.createActionFlee (b2);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (*m, Movement (&b1, "running from  (fast)", 13.0, 0.0));
}

TEST (Blob, chooses_to_flee)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 5.0, 1000.0, 0U, 0U, 0.5),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0, 5.0, 5.0, 0.0, 1U)};
	
	std::shared_ptr<Action> a = blobs [0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (m->_reason, "running from  (fast)");
}

TEST (Blob, chooses_not_to_flee_because_out_of_range)
{
	std::vector<Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 5.0, 5.0, 2.0, 2.0, 0.0),
		Blob ("", [](double) {return 0.0;}, 5.0, 10.0, 12.0, 12.0)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (m->_reason, "wandering");
}

TEST (Blob, chooses_not_to_flee_because_aggressive)
{
	std::vector<Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 5.0, 5.0, 2.0, 2.0, 1000.0),
		Blob ("", [](double) {return 0.0;}, 5.0, 10.0, 12.0, 12.0, 0.0, 10U)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (m->_reason, "wandering");
}

TEST (Blob, chooses_not_to_flee_because_stronger)
{
	std::vector<Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 5.0, 5.0, 2.0, 2.0, 1000.0, 10U),
		Blob ("", [](double) {return 0.0;}, 5.0, 10.0, 12.0, 12.0, 0.0)};

	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs);
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	EXPECT_EQ (m->_reason, "hunting  (fast)");
}

TEST (Blob, chooses_to_flee_from_strongest)
{
	std::vector <Blob> blobs {
		Blob ("", [](double) {return 0.0;}, 10.0, 10.0, 5.0, 5.0, 1000.0, 0U, 0U, 0.5),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0, 5.0, 5.0, 0.0, 1U),
		Blob ("", [](double) {return 0.0;}, 20.0, 20.0, 5.0, 5.0, 0.0, 2U)};
	
	std::shared_ptr<Action> a = blobs[0].chooseNextAction (blobs); 
	ASSERT_TRUE (std::dynamic_pointer_cast <Movement> (a));
	std::shared_ptr <Movement> m (std::dynamic_pointer_cast <Movement> (a));
	
	EXPECT_EQ (m->_reason, "running from  (fast)");
}

int main (int argc, char** argv) 
{
	testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}

