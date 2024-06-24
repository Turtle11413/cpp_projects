#include <gtest/gtest.h>

#include "../model/model.h"

TEST(ParserTest, ParseInvalidNameFile) {
  s21::Model model;

  std::string invalid_file_path = "asdg";
  EXPECT_THROW(model.LoadFile(invalid_file_path), std::invalid_argument);
}

TEST(ParserTest, ParseInvalidSize) {
  s21::Model model;

  std::string file_path = "test/invalid_size.txt";
  EXPECT_THROW(model.LoadFile(file_path), std::invalid_argument);
}

TEST(ParserTest, ParseInvalidElement) {
  s21::Model model;

  std::string file_path = "test/invalid_element.txt";
  EXPECT_THROW(model.LoadFile(file_path), std::invalid_argument);
}

TEST(ParserTest, ParseCorrectFile) {
  s21::Model model;

  std::string valid_file_path = "test/test.txt";

  model.LoadFile(valid_file_path);

  EXPECT_EQ(4, model.GetMaze().GetSize().first);
  EXPECT_EQ(4, model.GetMaze().GetSize().second);

  EXPECT_EQ(0, model.GetMaze()(0, 0).first);
  EXPECT_EQ(0, model.GetMaze()(0, 1).first);
  EXPECT_EQ(0, model.GetMaze()(0, 2).first);
  EXPECT_EQ(1, model.GetMaze()(0, 3).first);

  EXPECT_EQ(1, model.GetMaze()(1, 0).first);
  EXPECT_EQ(0, model.GetMaze()(1, 1).first);
  EXPECT_EQ(1, model.GetMaze()(1, 2).first);
  EXPECT_EQ(1, model.GetMaze()(1, 3).first);

  EXPECT_EQ(0, model.GetMaze()(2, 0).first);
  EXPECT_EQ(1, model.GetMaze()(2, 1).first);
  EXPECT_EQ(0, model.GetMaze()(2, 2).first);
  EXPECT_EQ(1, model.GetMaze()(2, 3).first);

  EXPECT_EQ(0, model.GetMaze()(3, 0).first);
  EXPECT_EQ(0, model.GetMaze()(3, 1).first);
  EXPECT_EQ(0, model.GetMaze()(3, 2).first);
  EXPECT_EQ(1, model.GetMaze()(3, 3).first);

  // ============================================ //

  EXPECT_EQ(1, model.GetMaze()(0, 0).second);
  EXPECT_EQ(0, model.GetMaze()(0, 1).second);
  EXPECT_EQ(1, model.GetMaze()(0, 2).second);
  EXPECT_EQ(0, model.GetMaze()(0, 3).second);

  EXPECT_EQ(0, model.GetMaze()(1, 0).second);
  EXPECT_EQ(0, model.GetMaze()(1, 1).second);
  EXPECT_EQ(1, model.GetMaze()(1, 2).second);
  EXPECT_EQ(0, model.GetMaze()(1, 3).second);

  EXPECT_EQ(1, model.GetMaze()(2, 0).second);
  EXPECT_EQ(1, model.GetMaze()(2, 1).second);
  EXPECT_EQ(0, model.GetMaze()(2, 2).second);
  EXPECT_EQ(1, model.GetMaze()(2, 3).second);

  EXPECT_EQ(1, model.GetMaze()(3, 0).second);
  EXPECT_EQ(1, model.GetMaze()(3, 1).second);
  EXPECT_EQ(1, model.GetMaze()(3, 2).second);
  EXPECT_EQ(1, model.GetMaze()(3, 3).second);
}
