#include "test_main.h"

// ---------------- CONSTRUCTORS ---------------- //

TEST(set_constructor, default_counstructor) {
  s21::set<int> s21_set_int;
  s21::set<double> s21_set_double;
  s21::set<std::string> s21_set_string;

  EXPECT_TRUE(s21_set_int.empty());
  EXPECT_EQ(s21_set_int.size(), 0U);

  EXPECT_TRUE(s21_set_double.empty());
  EXPECT_EQ(s21_set_double.size(), 0U);

  EXPECT_TRUE(s21_set_string.empty());
  EXPECT_EQ(s21_set_string.size(), 0U);
}

TEST(set_constructor, initializer_list_constructor) {
  s21::set<int> s21_set_int{4, 8, 1};
  std::set<int> std_set_int{4, 8, 1};

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }

  s21::set<double> s21_set_double{1.4, 4.8, 8.9};
  std::set<double> std_set_double{1.4, 4.8, 8.9};

  auto s21_it_doub = s21_set_double.begin();
  auto std_it_doub = std_set_double.begin();
  for (; s21_it_doub != s21_set_double.end() &&
         std_it_doub != std_set_double.end();
       ++s21_it_doub, ++std_it_doub) {
    EXPECT_EQ(*s21_it_doub, *std_it_doub);
  }

  s21::set<std::string> s21_set_string{"Hello", ",", "world"};
  std::set<std::string> std_set_string{"Hello", ",", "world"};

  auto s21_it_str = s21_set_string.begin();
  auto std_it_str = std_set_string.begin();
  for (;
       s21_it_str != s21_set_string.end() && std_it_str != std_set_string.end();
       ++s21_it_str, ++std_it_str) {
    EXPECT_EQ(*s21_it_str, *std_it_str);
  }
}

TEST(set_constructor, copy_construstor) {
  s21::set<int> s21_set_int{1, 2, 3};
  std::set<int> std_set_int{1, 2, 3};

  s21::set<int> s21_set_int2(s21_set_int);
  auto s21_it_int = s21_set_int2.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int2.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

// TEST(set_constructor, move_constructor) {}

// ---------------- OPERATORS ---------------- //

TEST(set_operator, copy) {
  s21::set<int> s21_set_int{1, 2, 3};
  std::set<int> std_set_int{1, 2, 3};

  s21::set<int> s21_set_int2 = s21_set_int;
  auto s21_it_int = s21_set_int2.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int2.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

// TEST(set_operator, move) {}

// ---------------- ITERATORS ---------------- //

TEST(set_iterator, begin) {
  s21::set<int> s21_set_int{1, 2, 3};
  std::set<int> std_set_int{1, 2, 3};

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  EXPECT_EQ(*s21_it_int, *std_it_int);
}

TEST(set_iterator, end) {
  s21::set<int> s21_set_int{1, 2, 3};

  auto s21_it_int = s21_set_int.end();
  EXPECT_EQ(*s21_it_int, 0);
}

// ---------------- CAPACITY ---------------- //

TEST(set_capacity, empty) {
  s21::set<int> s21_set_int;
  std::set<int> std_set_int;

  EXPECT_EQ(s21_set_int.empty(), std_set_int.empty());
}

TEST(set_capacity, empty1) {
  s21::set<int> s21_set_int{1, 2, 3};
  std::set<int> std_set_int{1, 2, 3, 4};

  EXPECT_EQ(s21_set_int.empty(), std_set_int.empty());
}

TEST(set_capacity, size) {
  s21::set<int> s21_set_int{1, 2, 3};
  std::set<int> std_set_int{1, 2, 3};

  EXPECT_EQ(s21_set_int.size(), std_set_int.size());
}

TEST(set_capacity, size1) {
  s21::set<int> s21_set_int{1, 2};
  std::set<int> std_set_int{1, 2, 3};

  EXPECT_TRUE(s21_set_int.size() != std_set_int.size());
}

TEST(set_capacity, max_size) {
  s21::set<int> s21_set_int{1, 2, 3};
  std::set<int> std_set_int{1, 2, 3};

  EXPECT_EQ(s21_set_int.max_size(), std_set_int.max_size());
}

// ---------------- MODIFIERS ---------------- //

TEST(set_modifiers, clear) {
  s21::set<int> s21_set{3, 2, 7, 6, 1, 2, 0, 3};
  s21_set.clear();

  EXPECT_TRUE(s21_set.empty());
}

TEST(set_modifiers, insert) {
  s21::set<int> s21_set_int{5, 12, 1, 7, 3};
  std::set<int> std_set_int{5, 12, 1, 7, 3, 10};

  s21_set_int.insert(10);

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, insert1) {
  s21::set<int> s21_set_int{5, 12, 1, 7, 3, 10};
  std::set<int> std_set_int{5, 12, 1, 7, 3, 10};

  s21_set_int.insert(10);

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, erase_key) {
  s21::set<int> s21_set_int{5, 12, 1, 7, 3, 10};
  std::set<int> std_set_int{5, 12, 1, 7, 3};

  s21_set_int.erase(10);

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, erase_key1) {
  s21::set<int> s21_set_int{5, 12, 1, 7, 3, 10};
  std::set<int> std_set_int{5, 12, 1, 3, 10};

  s21_set_int.erase(7);

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, erase_key2) {
  s21::set<int> s21_set_int{1, 2,  3,  4,  5,  6,  7,  8,
                            9, 10, 11, 12, 13, 14, 15, 16};
  std::set<int> std_set_int{1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  s21_set_int.erase(7);

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, erase_key3) {
  s21::set<int> s21_set_int{1, 2,  3,  4,  5,  6,  7,  8,
                            9, 10, 11, 12, 13, 14, 15, 16};
  std::set<int> std_set_int{1, 2, 3, 4, 5, 6, 8, 7, 10, 11, 12, 13, 14, 15, 16};

  s21_set_int.erase(9);

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, erase_key4) {
  s21::set<int> s21_set_int{1, 2,  3,  4,  5,  6,  7,  8,
                            9, 10, 11, 12, 13, 14, 15, 16};
  std::set<int> std_set_int{1, 2, 3, 4, 5, 6, 8, 7, 10, 11, 9, 13, 14, 15, 16};

  s21_set_int.erase(12);

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, erase_key5) {
  s21::set<int> b{1, 2, 3};
  b.insert(25);
  b.insert(4);
  b.insert(12);
  b.insert(9);
  b.insert(3);
  b.insert(5);
  b.insert(6);
  b.insert(1);
  b.insert(2);
  b.insert(10);
  b.insert(9);
  b.insert(11);
  b.insert(14);
  b.insert(13);
  b.insert(15);
  b.insert(16);

  b.erase(25);
  b.erase(4);
  b.erase(12);
  b.erase(9);
  b.erase(3);
  b.erase(5);
  b.erase(6);
  b.erase(1);
  b.erase(2);
  b.erase(10);
  b.erase(9);
  b.erase(11);
  b.erase(14);
  b.erase(13);
  b.erase(15);
  b.erase(16);

  EXPECT_TRUE(b.empty());
}

TEST(set_modifiers, erase_iterator) {
  s21::set<int> s21_set_int{5, 12, 1, 7, 3, 10};
  std::set<int> std_set_int{5, 12, 1, 7, 3, 10};

  s21_set_int.erase(s21_set_int.begin());
  std_set_int.erase(std_set_int.begin());

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();
  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, erase_iterator1) {
  s21::set<int> s21_set_int{5, 12, 1, 7, 3, 10};
  std::set<int> std_set_int{5, 12, 1, 7, 3, 10};

  s21_set_int.erase(s21_set_int.end());

  auto s21_it_int = s21_set_int.begin();
  auto std_it_int = std_set_int.begin();

  for (; s21_it_int != s21_set_int.end() && std_it_int != std_set_int.end();
       ++s21_it_int, ++std_it_int) {
    EXPECT_EQ(*s21_it_int, *std_it_int);
  }
}

TEST(set_modifiers, swap) {
  s21::set<int> s21_set_int{5, 12, 1, 7, 3, 10};  // -> {1, 2, 3}
  std::set<int> res1{1, 2, 3};

  s21::set<int> s21_set_int1{1, 2, 3};  // -> {5, 12, 1, 7, 3, 10}
  std::set<int> res2{5, 12, 1, 7, 3, 10};

  s21_set_int.swap(s21_set_int1);
  auto s21_it = s21_set_int.begin();
  auto res1_it = res1.begin();

  for (; s21_it != s21_set_int.end() && res1_it != res1.end();
       ++s21_it, ++res1_it) {
    EXPECT_EQ(*s21_it, *res1_it);
  }

  auto s21_it_1 = s21_set_int1.begin();
  auto res2_it = res2.begin();

  for (; s21_it_1 != s21_set_int1.end() && res2_it != res2.end();
       ++s21_it_1, ++res2_it) {
    EXPECT_EQ(*s21_it_1, *res2_it);
  }
}

TEST(set_modifiers, merge) {
  s21::set<int> set1{5, 2, 7, 1, 9, 9, 0};
  s21::set<int> set2{10, 1, 5, 2};
  set1.merge(set2);

  std::set<int> result{5, 2, 7, 1, 9, 0, 10};

  auto s21_it = set1.begin();
  auto std_it = result.begin();

  for (; s21_it != set1.end() && std_it != result.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(set_modifiers, insert_many) {
  s21::set<int> set1;
  set1.insert_many(66, 23, 1, 6, 3, 0);

  std::set<int> result{66, 23, 1, 6, 3, 0};

  auto s21_it = set1.begin();
  auto std_it = result.begin();

  for (; s21_it != set1.end() && std_it != result.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

// ---------------- LOOKUP ---------------- //

TEST(set_lookup, find) {
  s21::set<int> set1;
  set1.insert_many(66, 23, 1, 6, 3, 0);

  std::set<int> result{66, 23, 1, 6, 3, 0};

  auto it = set1.find(23);
  auto std_it = result.find(23);

  EXPECT_EQ(*it, *std_it);
}

TEST(set_lookup, contains) {
  s21::set<int> set1;
  set1.insert_many(66, 23, 1, 6, 3, 0);

  EXPECT_TRUE(set1.contains(66));
}
