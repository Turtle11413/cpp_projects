#include "test_main.h"

// ---------------- CONSTRUCTORS ---------------- //

TEST(multiset_constructor, default_counstructor) {
  s21::multiset<int> multiset_int;

  EXPECT_TRUE(multiset_int.empty());
  EXPECT_EQ(multiset_int.size(), 0U);
}

TEST(multiset_constructor, initializer_list_constructor) {
  s21::multiset<int> multiset_int{4, 8, 1};
  std::multiset<int> multiset{4, 8, 1};

  auto s21_it_int = multiset_int.begin();
  auto std_it_int = multiset.begin();
  for (; s21_it_int != multiset_int.end() && std_it_int != multiset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }

  s21::multiset<double> multiset_double{1.4, 4.8, 8.9};
  std::multiset<double> std_multiset{1.4, 4.8, 8.9};

  auto s21_it_doub = multiset_double.begin();
  auto std_it_doub = std_multiset.begin();
  for (; s21_it_doub != multiset_double.end() &&
         std_it_doub != std_multiset.end();
       ++s21_it_doub, ++std_it_doub) {
    EXPECT_EQ(*s21_it_doub, *std_it_doub);
  }

  s21::multiset<std::string> multiset_string{"Hello", ",", "world"};
  std::multiset<std::string> std_multiset_str{"Hello", ",", "world"};

  auto s21_it_str = multiset_string.begin();
  auto std_it_str = std_multiset_str.begin();
  for (; s21_it_str != multiset_string.end() &&
         std_it_str != std_multiset_str.end();
       ++s21_it_str, ++std_it_str) {
    EXPECT_EQ(*s21_it_str, *std_it_str);
  }
}

TEST(multiset_constructor, copy_construstor) {
  s21::multiset<int> my_mset{1, 2, 3};
  std::multiset<int> std_mset{1, 2, 3};

  s21::multiset<int> my_mset2(my_mset);
  auto s21_it_int = my_mset2.begin();
  auto std_it_int = std_mset.begin();
  for (; s21_it_int != my_mset2.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(multiset_constructor, move_constructor) {
  s21::multiset<int> my_mset{1, 2, 3};
  std::multiset<int> std_mset{1, 2, 3};

  s21::multiset<int> my_mset2(std::move(my_mset));
  auto s21_it_int = my_mset2.begin();
  auto std_it_int = std_mset.begin();
  for (; s21_it_int != my_mset2.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
  EXPECT_TRUE(my_mset.empty());
}

// ---------------- OPERATORS ---------------- //

TEST(multiset_operator, copy) {
  s21::multiset<int> my_mset{1, 2, 3};
  std::multiset<int> std_mset{1, 2, 3};

  s21::multiset<int> my_mset2 = my_mset;
  auto s21_it_int = my_mset2.begin();
  auto std_it_int = std_mset.begin();
  for (; s21_it_int != my_mset2.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

// ---------------- ITERATORS ---------------- //

TEST(multiset_iterator, begin) {
  s21::multiset<int> my_mset{1, 2, 3};
  std::multiset<int> std_mset{1, 2, 3};

  auto s21_it_int = my_mset.begin();
  auto std_it_int = std_mset.begin();
  EXPECT_EQ(*s21_it_int, *std_it_int);
}

TEST(multiset_iterator, end) {
  s21::multiset<int> my_mset{1, 2, 3};

  auto s21_it_int = my_mset.end();
  EXPECT_EQ(*s21_it_int, 0);
}

// ---------------- CAPACITY ---------------- //

// empty
TEST(multiset_capacity, empty) {
  s21::multiset<int> my_mset;
  std::multiset<int> std_mset;

  EXPECT_EQ(my_mset.empty(), std_mset.empty());
}

TEST(multiset_capacity, empty1) {
  s21::multiset<int> my_mset{1, 2, 3};
  std::multiset<int> std_mset{1, 2, 3, 4};

  EXPECT_EQ(my_mset.empty(), std_mset.empty());
}

// size
TEST(multiset_capacity, size) {
  s21::multiset<int> my_mset{1, 2, 3};
  std::multiset<int> std_set_int{1, 2, 3};

  EXPECT_EQ(my_mset.size(), std_set_int.size());
}

TEST(multiset_capacity, size1) {
  s21::multiset<int> my_mset{1, 2};
  std::multiset<int> std_set_int{1, 2, 3};

  EXPECT_TRUE(my_mset.size() != std_set_int.size());
}

TEST(multiset_capacity, max_size) {
  s21::multiset<int> my_mset{1, 2, 3};
  std::multiset<int> std_set_int{1, 2, 3};

  EXPECT_EQ(my_mset.max_size(), std_set_int.max_size());
}

// ---------------- MODIFIERS ---------------- //

// clear
TEST(multiset_modifiers, clear) {
  s21::multiset<int> my_mset{3, 2, 7, 6, 1, 2, 0, 3};
  my_mset.clear();

  EXPECT_TRUE(my_mset.empty());
}

// insert
TEST(multiset_modifiers, insert) {
  s21::multiset<int> my_mset{5, 12, 1, 7, 3};
  std::multiset<int> std_mset{5, 12, 1, 7, 3, 10};

  my_mset.insert(10);

  auto s21_it_int = my_mset.begin();
  auto std_it_int = std_mset.begin();
  for (; s21_it_int != my_mset.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(multiset_modifiers, insert1) {
  s21::multiset<int> my_mset{5, 12, 1, 7, 3, 10};
  std::multiset<int> std_mset{5, 12, 1, 7, 3, 10};

  my_mset.insert(10);
  std_mset.insert(10);

  auto s21_it_int = my_mset.begin();
  auto std_it_int = std_mset.begin();
  for (; s21_it_int != my_mset.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

// erase
TEST(multiset_modifiers, erase_key) {
  s21::multiset<int> my_mset{5, 12, 1, 7, 3, 10};
  std::multiset<int> std_mset{5, 12, 1, 7, 3};

  my_mset.erase(10);

  auto s21_it_int = my_mset.begin();
  auto std_it_int = std_mset.begin();
  for (; s21_it_int != my_mset.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(multiset_modifiers, erase_iterator) {
  s21::multiset<int> my_mset{5, 12, 1, 7, 3, 10};
  std::multiset<int> std_mset{5, 12, 1, 7, 3, 10};

  my_mset.erase(my_mset.begin());
  std_mset.erase(std_mset.begin());

  auto s21_it_int = my_mset.begin();
  auto std_it_int = std_mset.begin();
  for (; s21_it_int != my_mset.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(multiset_modifiers, erase_iterator1) {
  s21::multiset<int> my_mset{5, 12, 1, 7, 3, 10};
  std::multiset<int> std_mset{5, 12, 1, 7, 3, 10};

  my_mset.erase(my_mset.end());

  auto s21_it_int = my_mset.begin();
  auto std_it_int = std_mset.begin();

  for (; s21_it_int != my_mset.end() && std_it_int != std_mset.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

// swap
TEST(multiset_modifiers, swap) {
  s21::multiset<int> my_mset{5, 12, 1, 7, 3, 10}; // -> {1, 2, 3}
  std::multiset<int> res1{1, 2, 3};

  s21::multiset<int> my_mset1{1, 2, 3}; // -> {5, 12, 1, 7, 3, 10}
  std::multiset<int> res2{5, 12, 1, 7, 3, 10};

  my_mset.swap(my_mset1);
  auto s21_it = my_mset.begin();
  auto res1_it = res1.begin();

  for (; s21_it != my_mset.end() && res1_it != res1.end();
       ++s21_it, ++res1_it) {
    EXPECT_EQ(*s21_it, *res1_it);
  }

  auto s21_it_1 = my_mset1.begin();
  auto res2_it = res2.begin();

  for (; s21_it_1 != my_mset1.end() && res2_it != res2.end();
       ++s21_it_1, ++res2_it) {
    EXPECT_EQ(*s21_it_1, *res2_it);
  }
}

// merge
TEST(multiset_modifiers, merge) {
  s21::multiset<int> my_mset1{5, 2, 7, 1, 9, 9, 0};
  s21::multiset<int> my_mset2{10, 1, 5, 2};
  my_mset1.merge(my_mset2);

  std::multiset<int> result{5, 2, 7, 1, 9, 9, 0, 10, 1, 5, 2};

  auto s21_it = my_mset1.begin();
  auto std_it = result.begin();

  for (; s21_it != my_mset1.end() && std_it != result.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

// insert_many
TEST(multiset_modifiers, insert_many) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 6, 3, 0);

  std::multiset<int> result{66, 23, 1, 6, 3, 0};

  auto s21_it = my_mset1.begin();
  auto std_it = result.begin();

  for (; s21_it != my_mset1.end() && std_it != result.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

// ---------------- LOOKUP ---------------- //

// find
TEST(multiset_lookup, find) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 6, 3, 0);

  std::multiset<int> result{66, 23, 1, 6, 3, 0};

  auto it = my_mset1.find(23);
  auto std_it = result.find(23);

  EXPECT_EQ(*it, *std_it);
}

// contains
TEST(multiset_lookup, contains) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 6, 3, 0);

  EXPECT_TRUE(my_mset1.contains(66));
}

// count
TEST(multiset_lookup, count) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.count(1);
  auto std_res = result.count(1);

  EXPECT_EQ(my_res, std_res);
}

// lower_bound
TEST(multiset_lookup, lower_bound) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.lower_bound(1);
  auto std_res = result.lower_bound(1);

  EXPECT_EQ(*my_res, *std_res);
}

TEST(multiset_lookup, lower_bound1) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.lower_bound(23);
  auto std_res = result.lower_bound(23);

  EXPECT_EQ(*my_res, *std_res);
}

TEST(multiset_lookup, lower_bound2) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.lower_bound(2);
  auto std_res = result.lower_bound(2);

  EXPECT_EQ(*my_res, *std_res);
}

// upper_bound
TEST(multiset_lookup, upper_bound) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.upper_bound(1);
  auto std_res = result.upper_bound(1);

  EXPECT_EQ(*my_res, *std_res);
}

TEST(multiset_lookup, upper_bound1) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.upper_bound(23);
  auto std_res = result.upper_bound(23);

  EXPECT_EQ(*my_res, *std_res);
}

TEST(multiset_lookup, upper_bound2) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.upper_bound(2);
  auto std_res = result.upper_bound(2);

  EXPECT_EQ(*my_res, *std_res);
}

TEST(multiset_lookup, equal_range) {
  s21::multiset<int> my_mset1;
  my_mset1.insert_many(66, 23, 1, 1, 1, 0);

  std::multiset<int> result{66, 23, 1, 1, 1, 0};

  auto my_res = my_mset1.equal_range(1);
  auto std_res = result.equal_range(1);

  EXPECT_EQ(*(my_res.first), *(std_res.first));
  EXPECT_EQ(*(my_res.second), *(std_res.second));
}

// ---------------- MAIN ---------------- //
