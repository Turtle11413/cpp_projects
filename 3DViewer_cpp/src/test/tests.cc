#include <gtest/gtest.h>

#include <cmath>

#include "../viewer/model.h"
#include "../viewer/object.h"

class AffineTest : public testing::Test {
 protected:
  void SetUp() override { m.Parse("test/test.obj"); }
  s21::Model m;
};

TEST_F(AffineTest, rotate_x) {
  double angle = acos(-1) / 180;
  std::vector<double> result = {
      0,           cos(angle), sin(angle), -1,          sin(angle),
      -cos(angle), 1,          sin(angle), -cos(angle), 1,
      -sin(angle), cos(angle), -1,         -sin(angle), cos(angle)};

  m.RotateX(1);
  s21::Object &obj = m.Obj();

  for (unsigned int i = 0; i < obj.GetVerticesCount() - 1; ++i) {
    EXPECT_NEAR(obj[i], result[i], 1e-5);
  }
}

TEST_F(AffineTest, rotate_y) {
  double angle = acos(-1) / 180;
  std::vector<double> result = {0,
                                1,
                                0,
                                -cos(angle) - sin(angle),
                                0,
                                -cos(angle) + sin(angle),
                                cos(angle) - sin(angle),
                                0,
                                -cos(angle) - sin(angle),
                                cos(angle) + sin(angle),
                                0,
                                cos(angle) - sin(angle),
                                -cos(angle) + sin(angle),
                                0,
                                cos(angle) + sin(angle)};

  m.RotateY(1);
  s21::Object &obj = m.Obj();

  for (unsigned int i = 0; i < obj.GetVerticesCount() - 1; ++i) {
    EXPECT_NEAR(obj[i], result[i], 1e-5);
  }
}

TEST_F(AffineTest, rotate_z) {
  double angle = acos(-1) / 180;
  std::vector<double> result = {
      -sin(angle), cos(angle), 0,           -cos(angle), -sin(angle),
      -1,          cos(angle), sin(angle),  -1,          cos(angle),
      sin(angle),  1,          -cos(angle), -sin(angle), 1};

  m.RotateZ(1);
  s21::Object &obj = m.Obj();

  for (unsigned int i = 0; i < obj.GetVerticesCount() - 1; ++i) {
    EXPECT_NEAR(obj[i], result[i], 1e-5);
  }
}

TEST_F(AffineTest, scale) {
  std::vector<double> result = {0,       1 * 10, 0,       -1 * 10, 0,
                                -1 * 10, 1 * 10, 0,       -1 * 10, 1 * 10,
                                0,       1 * 10, -1 * 10, 0,       1 * 10};

  m.Scale(10);
  s21::Object &obj = m.Obj();

  for (unsigned int i = 0; i < obj.GetVerticesCount() - 1; ++i) {
    EXPECT_NEAR(obj[i], result[i], 1e-5);
  }
}

TEST(Parser, cube) {
  s21::Model m;
  m.Parse("test/cube.obj");
  EXPECT_EQ(m.Obj()[0], -0.5);
  EXPECT_EQ(m.Obj()[1], -0.5);
  EXPECT_EQ(m.Obj()[2], -0.5);

  EXPECT_EQ(m.Obj()[3], -0.5);
  EXPECT_EQ(m.Obj()[4], -0.5);
  EXPECT_EQ(m.Obj()[5], 0.5);

  EXPECT_EQ(m.Obj()[6], -0.5);
  EXPECT_EQ(m.Obj()[7], 0.5);
  EXPECT_EQ(m.Obj()[8], -0.5);

  EXPECT_EQ(m.Obj()[9], -0.5);
  EXPECT_EQ(m.Obj()[10], 0.5);
  EXPECT_EQ(m.Obj()[11], 0.5);

  EXPECT_EQ(m.Obj()[12], 0.5);
  EXPECT_EQ(m.Obj()[13], -0.5);
  EXPECT_EQ(m.Obj()[14], -0.5);

  EXPECT_EQ(m.Obj()[15], 0.5);
  EXPECT_EQ(m.Obj()[16], -0.5);
  EXPECT_EQ(m.Obj()[17], 0.5);

  EXPECT_EQ(m.Obj()[18], 0.5);
  EXPECT_EQ(m.Obj()[19], 0.5);
  EXPECT_EQ(m.Obj()[20], -0.5);

  EXPECT_EQ(m.Obj()[21], 0.5);
  EXPECT_EQ(m.Obj()[22], 0.5);
  EXPECT_EQ(m.Obj()[23], 0.5);

  EXPECT_EQ(m.Obj().Indexes()[0], 4);
  EXPECT_EQ(m.Obj().Indexes()[1], 0);

  EXPECT_EQ(m.Obj().Indexes()[2], 2);
  EXPECT_EQ(m.Obj().Indexes()[3], 0);

  EXPECT_EQ(m.Obj().Indexes()[4], 6);
  EXPECT_EQ(m.Obj().Indexes()[5], 2);

  EXPECT_EQ(m.Obj().Indexes()[6], 4);
  EXPECT_EQ(m.Obj().Indexes()[7], 6);

  EXPECT_EQ(m.Obj().Indexes()[8], 5);
  EXPECT_EQ(m.Obj().Indexes()[9], 1);

  EXPECT_EQ(m.Obj().Indexes()[10], 3);
  EXPECT_EQ(m.Obj().Indexes()[11], 1);

  EXPECT_EQ(m.Obj().Indexes()[12], 7);
  EXPECT_EQ(m.Obj().Indexes()[13], 3);

  EXPECT_EQ(m.Obj().Indexes()[14], 5);
  EXPECT_EQ(m.Obj().Indexes()[15], 7);

  EXPECT_EQ(m.Obj().Indexes()[16], 2);
  EXPECT_EQ(m.Obj().Indexes()[17], 0);

  EXPECT_EQ(m.Obj().Indexes()[18], 1);
  EXPECT_EQ(m.Obj().Indexes()[19], 0);

  EXPECT_EQ(m.Obj().Indexes()[20], 3);
  EXPECT_EQ(m.Obj().Indexes()[21], 1);

  EXPECT_EQ(m.Obj().Indexes()[22], 2);
  EXPECT_EQ(m.Obj().Indexes()[23], 3);

  EXPECT_EQ(m.Obj().Indexes()[24], 6);
  EXPECT_EQ(m.Obj().Indexes()[25], 4);

  EXPECT_EQ(m.Obj().Indexes()[26], 5);
  EXPECT_EQ(m.Obj().Indexes()[27], 4);

  EXPECT_EQ(m.Obj().Indexes()[28], 7);
  EXPECT_EQ(m.Obj().Indexes()[29], 5);

  EXPECT_EQ(m.Obj().Indexes()[30], 6);
  EXPECT_EQ(m.Obj().Indexes()[31], 7);

  EXPECT_EQ(m.Obj().Indexes()[32], 4);
  EXPECT_EQ(m.Obj().Indexes()[33], 0);

  EXPECT_EQ(m.Obj().Indexes()[34], 1);
  EXPECT_EQ(m.Obj().Indexes()[35], 0);

  EXPECT_EQ(m.Obj().Indexes()[36], 5);
  EXPECT_EQ(m.Obj().Indexes()[37], 1);

  EXPECT_EQ(m.Obj().Indexes()[38], 4);
  EXPECT_EQ(m.Obj().Indexes()[39], 5);

  EXPECT_EQ(m.Obj().Indexes()[40], 6);
  EXPECT_EQ(m.Obj().Indexes()[41], 2);

  EXPECT_EQ(m.Obj().Indexes()[42], 3);
  EXPECT_EQ(m.Obj().Indexes()[43], 2);

  EXPECT_EQ(m.Obj().Indexes()[44], 7);
  EXPECT_EQ(m.Obj().Indexes()[45], 3);

  EXPECT_EQ(m.Obj().Indexes()[46], 6);
  EXPECT_EQ(m.Obj().Indexes()[47], 7);
}
