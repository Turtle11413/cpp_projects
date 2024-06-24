#ifndef S21_CONTAINERS_S21_MAP_MAP_H_
#define S21_CONTAINERS_S21_MAP_MAP_H_

#include <stdexcept>

#include "../rbtree/s21_rbtree.h"
#include "../vector/s21_vector.h"

namespace s21 {
using namespace rbtree;

template <typename Key, typename T> class map {
public:
  class MapIterator;
  class MapConstIterator;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = size_t;

  // map member functions
  map() noexcept : rb() {}
  map(std::initializer_list<value_type> const &items) {
    for (auto it : items) {
      insert(it);
    }
  }
  map(const map &m) { *this = m; }
  map(map &&m) noexcept { *this = std::move(m); }
  ~map() noexcept {};
  map &operator=(const map &m) {
    if (this != &m) {
      rb.clear();
      rb = m.rb;
    }
    return *this;
  }
  map &operator=(map &&m) noexcept {
    if (this != &m) {
      rb.clear();
      rb = std::move(m.rb);
    }
    return *this;
  }

  // map element access
  T &at(const Key &key) {
    iterator it = rb.find(key);
    if (it == end()) {
      throw std::out_of_range("No key in the map");
    } else {
      return (*it).second;
    }
  }
  T &operator[](const Key &key) {
    if (contains(key)) {
      return *(rb.find(key));
    } else {
      std::pair<iterator, bool> p = insert(key, mapped_type());
      return (*(p.first)).second;
    }
  }

  // map iterators
  iterator begin() noexcept { return rb.begin(); }
  iterator end() noexcept { return rb.end(); }

  class MapIterator : public TreeIterator<Key, T> {
  public:
    using TreeIterator<Key, T>::TreeIterator;
    MapIterator(const TreeIterator<Key, T> &other)
        : MapIterator(other.current_, other.end_) {}
    std::pair<key_type, mapped_type &> operator*() const noexcept {
      return std::pair<key_type, mapped_type &>(this->current_->key_,
                                                this->current_->value_);
    }
    MapIterator operator+(const size_type rhs) const noexcept {
      MapIterator it(*this);
      return it.MoveIterator(rhs, true);
    }
    MapIterator operator-(const size_type rhs) const noexcept {
      MapIterator it(*this);
      return it.MoveIterator(rhs, false);
    }
    MapIterator &operator++() noexcept { return *this += 1; }
    MapIterator &operator--() noexcept { return *this -= 1; }
    MapIterator &operator+=(const size_type rhs) noexcept {
      *this = *this + rhs;
      return *this;
    }
    MapIterator &operator-=(const size_type rhs) noexcept {
      *this = *this - rhs;
      return *this;
    }
  };
  class MapConstIterator : public TreeConstIterator<Key, T> {
  public:
    using TreeConstIterator<Key, T>::TreeConstIterator;
    MapConstIterator(const TreeConstIterator<Key, T> &other)
        : MapConstIterator(other.current_, other.end_) {}
    const value_type operator*() const noexcept {
      return std::pair<key_type, mapped_type>(this->current_->key_,
                                              this->current_->value_);
    }
    MapConstIterator operator+(const size_type rhs) const noexcept {
      MapConstIterator it(*this);
      return it.MoveIterator(rhs, true);
    }
    MapConstIterator operator-(const size_type rhs) const noexcept {
      MapConstIterator it(*this);
      return it.MoveIterator(rhs, false);
    }
    MapConstIterator &operator++() noexcept { return *this += 1; }
    MapConstIterator &operator--() noexcept { return *this -= 1; }
    MapConstIterator &operator+=(const size_type rhs) noexcept {
      *this = *this + rhs;
      return *this;
    }
    MapConstIterator &operator-=(const size_type rhs) noexcept {
      *this = *this - rhs;
      return *this;
    }
  };

  // map capacity
  bool empty() const noexcept { return rb.root_ == nullptr; }
  size_type size() const noexcept { return rb.size(); }
  size_type max_size() const noexcept { return rb.max_size(); }

  // map modifiers
  void clear() noexcept { rb.clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    return rb.insert(value.first, value.second, true);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return rb.insert(key, obj, true);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    std::pair<iterator, bool> p = insert(key, obj);
    if (!p.second) {
      *(rb.find(key)) = obj;
    }
    return p;
  }
  void erase(iterator pos) noexcept { rb.erase(pos); }
  void erase(const key_type &key) noexcept { rb.erase(key); }
  void swap(map &other) noexcept { rb.swap(other.rb); }
  void merge(map &other) {
    for (auto it : other) {
      insert(it);
    }
  }
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) noexcept {
    vector<std::pair<iterator, bool>> res;

    res.reserve(sizeof...(args));
    for (auto &&arg : {args...}) {
      res.push_back(rb.insert(arg.first, arg.second, true));
    }
    return res;
  }

  // map lookup
  bool contains(const Key &key) const noexcept { return rb.contains(key); }

private:
  RBTree<key_type, mapped_type> rb;
};
}; // namespace s21

#endif // S21_CONTAINERS_S21_MAP_H_
