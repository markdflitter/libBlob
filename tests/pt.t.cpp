#include <gtest/gtest.h>

#include <pt.h>

TEST (pt, createEmpty) {
  Pt<int> p;

  ASSERT_EQ (p.x (), 0);
  ASSERT_EQ (p.y (), 0);
}

TEST (pt, create) {
  Pt<int> p {10,20};

  ASSERT_EQ (p.x (), 10);
  ASSERT_EQ (p.y (), 20);
}

TEST (pt, update) {
  Pt<int> p {10,20};

  p.x () = 30;
  ASSERT_EQ (p.x (), 30);

  p.y () = 40;
  ASSERT_EQ (p.x (), 30);
  ASSERT_EQ (p.y (), 40);
}

int main (int argc, char** argv) {
  testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();

}


