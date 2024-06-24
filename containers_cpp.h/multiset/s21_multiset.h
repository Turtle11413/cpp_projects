#ifndef S21_CONTAINERS_S21_MULTISET_MULTISET_H_
#define S21_CONTAINERS_S21_MULTISET_MULTISET_H_

#include <initializer_list>
#include <limits>
#include <new>
#include <stdexcept>
#include <utility>

#include "../rbtree/s21_rbtree.h"
#include "../vector/s21_vector.h"

namespace s21 {
using namespace rbtree;

template <typename Key>
class multiset {
 public:
  class multisetIterator;
  class multisetConstIterator;
  using value_type = Key;
  using key_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = multisetIterator;
  using const_iterator = multisetConstIterator;
  using size_type = size_t;

  // set member functions
  multiset() : rb() {}
  multiset(std::initializer_list<value_type> const &items) {
    for (const_reference value_ : items) {
      rb.insert(value_, value_, false);
    }
  }
  multiset(const multiset &s) { *this = s; }
  multiset(multiset &&s) { *this = std::move(s); }
  multiset &operator=(const multiset &s) {
    if (this != &s) {
      clear();
      rb = s.rb;
    }
    return *this;
  }
  multiset &operator=(multiset &&s) {
    if (this != &s) {
      clear();
      rb = std::move(s.rb);
    }
    return *this;
  }
  ~multiset(){};

  // Iterators
  iterator begin() { return rb.begin(); }
  iterator end() { return rb.end(); }

  // Capacity
  bool empty() const noexcept { return rb.root_ == nullptr; }
  size_type size() const noexcept { return rb.size(); }
  size_type max_size() const noexcept { return rb.max_size(); }

  // Modifiers
  void clear() { rb.clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<Node<value_type, key_type> *, bool> p;
    p = rb.insert(value, value, false);
    multisetIterator it(p.first, &rb.end_node_);
    return std::pair<multisetIterator, bool>(it, p.second);
  }

  void erase(iterator pos) { rb.erase(pos); }
  void erase(const key_type &key) { rb.erase(key); }
  void swap(multiset &other) { rb.swap(other.rb); }
  void merge(multiset &other) {
    for (auto it : other) {
      insert(it);
    }
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) noexcept {
    vector<std::pair<iterator, bool>> res;

    res.reserve(sizeof...(args));
    for (auto &&arg : {args...}) {
      res.push_back(rb.insert(arg, arg, false));
    }
    return res;
  }

  // Lookup
  iterator find(const Key &key) { return rb.find(key); }
  bool contains(const Key &key) { return rb.contains(key); }
  size_type count(const Key &key) { return rb.count(key); }
  std::pair<iterator, iterator> equal_range(const Key &key) {
    iterator start(find(key)), finish(start);
    if (finish != end()) {
      for (; finish + 1 != end() && *(finish) == key; ++finish)
        ;
    }
    return std::pair<iterator, iterator>(start, finish);
  }
  iterator lower_bound(const Key &key) { return rb.lower_bound(key); }
  iterator upper_bound(const Key &key) { return rb.upper_bound(key); }

  class multisetIterator : public TreeIterator<value_type> {
   public:
    using TreeIterator<value_type>::TreeIterator;
    multisetIterator(const TreeIterator<value_type, key_type> &other)
        : multisetIterator(other.current_, other.end_) {}
  };
  class multisetConstIterator : public TreeConstIterator<value_type> {
   public:
    using TreeConstIterator<value_type>::TreeConstIterator;
    multisetConstIterator(const TreeIterator<value_type, key_type> &other)
        : multisetConstIterator(other.current_, other.end_) {}
  };

 private:
  RBTree<value_type, key_type> rb;
};
};  // namespace s21

#endif  //  S21_CONTAINERS_S21_MULTISET_MULTISET_H_
