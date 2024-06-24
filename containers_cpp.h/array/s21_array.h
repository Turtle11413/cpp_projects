#ifndef S21_CONTAINERS_S21_ARRAY_ARRAY_H_
#define S21_CONTAINERS_S21_ARRAY_ARRAY_H_

#include <climits>
#include <cstring>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T, size_t Nm> class array {
public:
  // array member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // array member functions
  array() noexcept : start(new value_type[Nm]), len(Nm) {}
  array(std::initializer_list<value_type> const &items) : array() {
    copy_contents(start, items.begin(), items.size() > Nm ? Nm : items.size());
  }
  array(const array &a) : array() { *this = a; }
  array(array &&a) noexcept : start(nullptr), len(Nm) { *this = std::move(a); }
  ~array() noexcept { delete[] start; }
  array &operator=(const array &a) noexcept {
    if (this != &a) {
      copy_contents(start, a.start, len);
    }
    return *this;
  }
  array &operator=(array &&a) noexcept {
    if (this != &a) {
      delete[] start;
      start = a.start;
      a.start = nullptr;
      a.len = 0;
    }
    return *this;
  }

  // array element access
  reference at(size_type pos) const {
    if (pos >= len) {
      throw std::out_of_range("pos is out of the scope");
    } else {
      return start[pos];
    }
  }
  reference operator[](size_type pos) const noexcept { return start[pos]; }
  const_reference front() const noexcept { return start[0]; }
  const_reference back() const noexcept { return start[len - 1]; }
  iterator data() const noexcept { return start; }

  // array iterators
  iterator begin() const noexcept { return start; }
  iterator end() const noexcept { return start + len; }

  // array capacity
  bool empty() const noexcept { return len == 0; }
  size_type size() const noexcept { return len; }
  size_type max_size() const noexcept { return LONG_MAX / sizeof(value_type); }

  // array modifiers
  void swap(array &other) noexcept {
    iterator tempi = other.start;
    other.start = start;
    start = tempi;
  }
  void fill(const_reference value) noexcept {
    for (size_type i = 0; i < len; ++i) {
      start[i] = value;
    }
  }

private:
  iterator start;
  size_type len;

  void copy_contents(iterator dest, const_iterator src,
                     size_type count) noexcept {
    for (size_type i = 0; i < count; ++i) {
      dest[i] = src[i];
    }
  }
};
} // namespace s21

#endif // S21_CONTAINERS_S21_ARRAY_ARRAY_H_
