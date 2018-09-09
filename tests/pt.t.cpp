#include <gtest/gtest.h>
#include <pt.h>

TEST (Pt, createEmpty) {
  Pt<double> p;

  EXPECT_DOUBLE_EQ (p.x (), 0.0);
  EXPECT_DOUBLE_EQ (p.y (), 0.0);
}

TEST (Pt, create) {
  Pt<double> p (10.0, 20.0);

  EXPECT_DOUBLE_EQ (p.x (), 10.0);
  EXPECT_DOUBLE_EQ (p.y (), 20.0);
}

TEST (Pt, update) {
  Pt<double> p (10.0, 20.0);

  p.x () = 30.0;
  EXPECT_DOUBLE_EQ (p.x (), 30.0);

  p.y () = 40.0;
  EXPECT_DOUBLE_EQ (p.x (), 30.0);
  EXPECT_DOUBLE_EQ (p.y (), 40.0);
}

int main (int argc, char** argv) {
  testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS();

}

