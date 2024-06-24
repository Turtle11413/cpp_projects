#ifndef S21_CONTAINERS_S21_SET_SET_H_
#define S21_CONTAINERS_S21_SET_SET_H_

#include <climits>
#include <initializer_list>
#include <new>
#include <stdexcept>

#include "../rbtree/s21_rbtree.h"
#include "../vector/s21_vector.h"

namespace s21 {
using namespace rbtree;

template <typename Key>
class set {
 public:
  class SetIterator;
  class SetConstIterator;
  using value_type = Key;
  using key_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;
  using size_type = size_t;

  // set member functions
  set() noexcept : rb() {}
  set(std::initializer_list<value_type> const &items) {
    for (const_reference value_ : items) {
      rb.insert(value_, value_, true);
    }
  }
  set(const set &s) { *this = s; }
  set(set &&s) noexcept { *this = std::move(s); }
  set &operator=(const set &s) {
    if (this != &s) {
      clear();
      rb = s.rb;
    }
    return *this;
  }
  set &operator=(set &&s) noexcept {
    if (this != &s) {
      clear();
      rb = std::move(s.rb);
    }
    return *this;
  }
  ~set() noexcept {};

  // Iterators
  iterator begin() noexcept { return rb.begin(); }
  iterator end() noexcept { return rb.end(); }

  class SetIterator : public TreeIterator<value_type> {
   public:
    using TreeIterator<value_type>::TreeIterator;
    SetIterator(const TreeIterator<value_type, key_type> &other)
        : SetIterator(other.current_, other.end_) {}
  };
  class SetConstIterator : public TreeConstIterator<value_type> {
   public:
    using TreeConstIterator<value_type>::TreeConstIterator;
    SetConstIterator(const TreeIterator<value_type, key_type> &other)
        : SetConstIterator(other.current_, other.end_) {}
  };

  // Capacity
  bool empty() const noexcept { return rb.root_ == nullptr; }
  size_type size() const noexcept { return rb.size(); }
  size_type max_size() const noexcept { return rb.max_size(); }

  // Modifiers
  void clear() noexcept { rb.clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<Node<value_type, key_type> *, bool> p;
    p = rb.insert(value, value, true);
    SetIterator it(p.first, &rb.end_node_);
    return std::pair<SetIterator, bool>(it, p.second);
  }
  void erase(iterator pos) noexcept { rb.erase(pos); }
  void erase(const key_type &key) noexcept { rb.erase(key); }
  void swap(set &other) noexcept { rb.swap(other.rb); }
  void merge(set &other) {
    for (auto it : other) {
      insert(it);
    }
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) noexcept {
    vector<std::pair<iterator, bool>> res;

    res.reserve(sizeof...(args));
    for (auto &&arg : {args...}) {
      res.push_back(rb.insert(arg, arg, true));
    }
    return res;
  }

  // Lookup
  iterator find(const Key &key) noexcept { return rb.find(key); }
  bool contains(const Key &key) const noexcept { return rb.contains(key); }

 private:
  RBTree<value_type, key_type> rb;
};
};  // namespace s21

#endif  // S21_CONTAINERS_S21_SET_SET_H_
