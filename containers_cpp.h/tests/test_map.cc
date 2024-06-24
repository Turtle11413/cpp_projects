#include "test_main.h"

class MapTest : public testing::Test {
 protected:
  std::pair<int, std::string> p11{1, "55"};
  std::pair<int, std::string> p12{8, "asdff"};
  std::pair<int, std::string> p13{999, "xd xd"};
  std::pair<double, double> p21{1.1, 0};
  std::pair<double, double> p22{11.11, 7.27};
  std::pair<double, double> p23{13.37, 99.9};
  s21::map<int, std::string> int_string{p11, p12, p13};
  s21::map<double, double> double_double{p23, p22, p21};
  s21::map<std::string, int> string_int{};
};

TEST_F(MapTest, caseCopy) {
  s21::map<int, std::string> int_string_2 = int_string;
  s21::map<double, double> double_double_2 = double_double;
  s21::map<std::string, int> string_int_2 = string_int;

  EXPECT_EQ(int_string_2.size(), 3U);
  EXPECT_EQ(double_double_2.size(), 3U);
  EXPECT_EQ(string_int_2.size(), 0U);
}

TEST_F(MapTest, caseMove) {
  s21::map<int, std::string> int_string_2 = std::move(int_string);
  s21::map<double, double> double_double_2 = std::move(double_double);
  s21::map<std::string, int> string_int_2 = std::move(string_int);

  EXPECT_EQ(int_string_2.size(), 3U);
  EXPECT_EQ(double_double_2.size(), 3U);
  EXPECT_EQ(string_int_2.size(), 0U);
  EXPECT_EQ(int_string.size(), 0U);
  EXPECT_EQ(double_double.size(), 0U);
  EXPECT_EQ(string_int.size(), 0U);
}

TEST_F(MapTest, caseAt1) {
  EXPECT_EQ(int_string.at(1), "55");
  EXPECT_EQ(int_string.at(8), "asdff");
  EXPECT_EQ(int_string.at(999), "xd xd");
  EXPECT_EQ(double_double.at(1.1), 0);
  EXPECT_EQ(double_double.at(11.11), 7.27);
  EXPECT_EQ(double_double.at(13.37), 99.9);
}

TEST_F(MapTest, caseAt2) {
  EXPECT_THROW(int_string.at(2), std::out_of_range);
  EXPECT_THROW(double_double.at(5.6), std::out_of_range);
  EXPECT_THROW(string_int.at("wysi"), std::out_of_range);
}

TEST_F(MapTest, caseAt3) {
  int_string.at(1) = "228";
  double_double.at(11.11) = 12.12;

  EXPECT_EQ(int_string.at(1), "228");
  EXPECT_EQ(double_double.at(11.11), 12.12);
}

TEST_F(MapTest, caseBraces1) {
  EXPECT_EQ(int_string[1], "55");
  EXPECT_EQ(double_double[11.11], 7.27);
}

TEST_F(MapTest, caseBraces2) { EXPECT_EQ(string_int["test"], int()); }

TEST_F(MapTest, caseBraces3) {
  int_string[1] = "228";
  double_double[11.11] = 12.12;

  EXPECT_EQ(int_string[1], "228");
  EXPECT_EQ(double_double[11.11], 12.12);
}

TEST_F(MapTest, caseBraces4) {
  string_int["test"] = 777;

  EXPECT_EQ(string_int["test"], 777);
}

TEST_F(MapTest, caseBeginEnd) {
  auto is_begin = int_string.begin();
  auto is_end = int_string.end();
  auto dd_begin = double_double.begin();
  auto dd_end = double_double.end();
  auto si_begin = string_int.begin();
  auto si_end = string_int.end();

  EXPECT_NE(is_begin, is_end);
  EXPECT_NE(dd_begin, dd_end);
  EXPECT_EQ(si_begin, si_end);

  EXPECT_EQ((*is_begin).first, 1);
  EXPECT_EQ((*dd_begin).first, 1.1);
  EXPECT_EQ((*is_begin).second, "55");
  EXPECT_EQ((*dd_begin).second, 0);
}

// iterators

TEST_F(MapTest, caseEmpty) {
  EXPECT_NE(int_string.empty(), true);
  EXPECT_NE(double_double.empty(), true);
  EXPECT_EQ(string_int.empty(), true);
}

TEST_F(MapTest, caseSize) {
  EXPECT_EQ(int_string.size(), 3U);
  EXPECT_EQ(double_double.size(), 3U);
  EXPECT_EQ(string_int.size(), 0U);
}

TEST_F(MapTest, caseClear) {
  int_string.clear();
  double_double.clear();
  string_int.clear();

  EXPECT_EQ(int_string.empty(), true);
  EXPECT_EQ(double_double.empty(), true);
  EXPECT_EQ(string_int.empty(), true);
}

TEST_F(MapTest, caseInsert1) {
  std::pair<int, std::string> is(2, "xd");
  std::pair<double, double> dd(0, 2.77);
  std::pair<std::string, int> si("1337", 727);

  auto is_res = int_string.insert(is);
  auto dd_res = double_double.insert(dd);
  auto si_res = string_int.insert(si);

  EXPECT_EQ(int_string[2], "xd");
  EXPECT_EQ(double_double[0], 2.77);
  EXPECT_EQ(string_int["1337"], 727);

  EXPECT_EQ(int_string.size(), 4U);
  EXPECT_EQ(double_double.size(), 4U);
  EXPECT_EQ(string_int.size(), 1U);

  EXPECT_EQ(is_res.second, true);
  EXPECT_EQ(dd_res.second, true);
  EXPECT_EQ(si_res.second, true);
}

TEST_F(MapTest, caseInsert2) {
  std::pair<int, std::string> is(999, "xd");
  std::pair<double, double> dd(13.37, 2.77);

  auto is_res = int_string.insert(is);
  auto dd_res = double_double.insert(dd);

  EXPECT_EQ(int_string[999], "xd xd");
  EXPECT_EQ(double_double[13.37], 99.9);

  EXPECT_EQ(int_string.size(), 3U);
  EXPECT_EQ(double_double.size(), 3U);

  EXPECT_EQ(is_res.second, false);
  EXPECT_EQ(dd_res.second, false);
}

TEST_F(MapTest, caseInsert3) {
  auto is_res = int_string.insert(2, "xd");
  auto dd_res = double_double.insert(0, 2.77);
  auto si_res = string_int.insert("1337", 727);

  EXPECT_EQ(int_string[2], "xd");
  EXPECT_EQ(double_double[0], 2.77);
  EXPECT_EQ(string_int["1337"], 727);

  EXPECT_EQ(int_string.size(), 4U);
  EXPECT_EQ(double_double.size(), 4U);
  EXPECT_EQ(string_int.size(), 1U);

  EXPECT_EQ(is_res.second, true);
  EXPECT_EQ(dd_res.second, true);
  EXPECT_EQ(si_res.second, true);
}

TEST_F(MapTest, caseInsert4) {
  auto is_res = int_string.insert(999, "xd");
  auto dd_res = double_double.insert(13.37, 2.77);

  EXPECT_EQ(int_string[999], "xd xd");
  EXPECT_EQ(double_double[13.37], 99.9);

  EXPECT_EQ(int_string.size(), 3U);
  EXPECT_EQ(double_double.size(), 3U);

  EXPECT_EQ(is_res.second, false);
  EXPECT_EQ(dd_res.second, false);
}

TEST_F(MapTest, caseInsertOrAssign1) {
  auto is_res = int_string.insert_or_assign(2, "xd");
  auto dd_res = double_double.insert_or_assign(0, 2.77);
  auto si_res = string_int.insert_or_assign("1337", 727);

  EXPECT_EQ(int_string[2], "xd");
  EXPECT_EQ(double_double[0], 2.77);
  EXPECT_EQ(string_int["1337"], 727);

  EXPECT_EQ(int_string.size(), 4U);
  EXPECT_EQ(double_double.size(), 4U);
  EXPECT_EQ(string_int.size(), 1U);

  EXPECT_EQ(is_res.second, true);
  EXPECT_EQ(dd_res.second, true);
  EXPECT_EQ(si_res.second, true);
}

TEST_F(MapTest, caseInsertOrAssign2) {
  auto is_res = int_string.insert_or_assign(999, "xd");
  auto dd_res = double_double.insert_or_assign(13.37, 2.77);

  EXPECT_EQ(int_string[999], "xd");
  EXPECT_EQ(double_double[13.37], 2.77);

  EXPECT_EQ(int_string.size(), 3U);
  EXPECT_EQ(double_double.size(), 3U);

  EXPECT_EQ(is_res.second, false);
  EXPECT_EQ(dd_res.second, false);
}

TEST_F(MapTest, caseErase1) {
  auto is_it = ++int_string.begin();
  auto dd_it = ++double_double.begin();

  EXPECT_EQ((*is_it).second, "asdff");
  EXPECT_EQ((*dd_it).second, 7.27);

  int_string.erase(is_it);
  double_double.erase(dd_it);

  is_it = ++int_string.begin();
  dd_it = ++double_double.begin();

  EXPECT_NE((*is_it).second, "asdff");
  EXPECT_NE((*dd_it).second, 7.27);
}

TEST_F(MapTest, caseErase2) {
  int_string.erase(8);
  double_double.erase(999);

  EXPECT_THROW(int_string.at(8), std::out_of_range);
  EXPECT_THROW(double_double.at(999), std::out_of_range);
}

TEST_F(MapTest, caseSwap) {
  s21::map<int, std::string> is_2{
      {2, "66"}, {9, "qwertt"}, {998, "lmao lmao"}, {123, "456"}};
  is_2.swap(int_string);

  EXPECT_EQ(is_2.at(1), "55");
  EXPECT_EQ(is_2.at(8), "asdff");
  EXPECT_EQ(is_2.at(999), "xd xd");
  EXPECT_EQ(is_2.size(), 3U);
  EXPECT_EQ((*(++is_2.end())).second, "xd xd");

  EXPECT_EQ(int_string.at(2), "66");
  EXPECT_EQ(int_string.at(9), "qwertt");
  EXPECT_EQ(int_string.at(998), "lmao lmao");
  EXPECT_EQ(int_string.at(123), "456");
  EXPECT_EQ(int_string.size(), 4U);
  EXPECT_EQ((*(++int_string.end())).second, "lmao lmao");
}

TEST_F(MapTest, caseMerge) {
  s21::map<int, std::string> is_2{
      {2, "66"}, {9, "qwertt"}, {999, "lmao lmao"}, {123, "456"}};
  int_string.merge(is_2);

  EXPECT_EQ(int_string.at(1), "55");
  EXPECT_EQ(int_string.at(2), "66");
  EXPECT_EQ(int_string.at(8), "asdff");
  EXPECT_EQ(int_string.at(9), "qwertt");
  EXPECT_EQ(int_string.at(999), "xd xd");
  EXPECT_EQ(int_string.at(123), "456");
  EXPECT_EQ(int_string.size(), 6U);
}

TEST_F(MapTest, caseInsertMany) {
  std::pair<int, std::string> p1(2, "66"), p2(9, "qwertt"),
      p3(999, "lmao lmao");
  auto res = int_string.insert_many(p1, p2, p3);

  EXPECT_EQ(int_string.at(2), "66");
  EXPECT_EQ(int_string.at(9), "qwertt");
  EXPECT_EQ(int_string.at(999), "xd xd");
  EXPECT_EQ(int_string.size(), 5U);

  EXPECT_EQ(res[0].second, true);
  EXPECT_EQ(res[1].second, true);
  EXPECT_EQ(res[2].second, false);
}

TEST_F(MapTest, caseContains) {
  EXPECT_EQ(int_string.contains(1), true);
  EXPECT_EQ(double_double.contains(1.1), true);
  EXPECT_EQ(string_int.contains("5"), false);
}
