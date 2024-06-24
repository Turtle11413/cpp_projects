#ifndef S21_CONTAINERS_S21_VECTOR_VECTOR_H_
#define S21_CONTAINERS_S21_VECTOR_VECTOR_H_

#include <climits>
#include <cstring>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 public:
  // vector member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // vector member functions
  vector() noexcept : start(nullptr), finish(nullptr), allocd(0) {}
  explicit vector(size_type n) {
    start = new value_type[n]();
    allocd = n;
    finish = start + n;
  }
  vector(std::initializer_list<value_type> const &items) : vector() {
    reserve(items.size());
    for (auto it : items) {
      push_back(it);
    }
  }
  vector(const vector &v) : vector() {
    if (this != &v && !v.empty()) {
      reserve(v.size());
      copy_contents(start, v.start, v.size());
      finish += v.size();
    }
  }
  vector(vector &&v) noexcept : vector() { *this = std::move(v); }
  ~vector() noexcept { delete[] start; }
  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] start;
      start = v.start;
      finish = v.finish;
      allocd = v.allocd;
      v.null();
    }
    return *this;
  }

  // vector element access
  reference at(size_type pos) const {
    if (pos >= size()) {
      throw std::out_of_range("pos is out of the scope");
    } else {
      return start[pos];
    }
  }
  reference operator[](size_type pos) const noexcept { return start[pos]; }
  const_reference front() const noexcept { return start[0]; }
  const_reference back() const noexcept { return finish[-1]; }
  iterator data() const noexcept { return start; }

  // vector iterators
  iterator begin() const noexcept { return start; }
  iterator end() const noexcept { return finish; }

  // vector capacity
  bool empty() const noexcept { return size() == 0; }
  size_type size() const noexcept { return finish - start; }
  size_type max_size() const noexcept { return LONG_MAX / sizeof(value_type); }
  void reserve(size_type size) {
    if (size >= this->size() && size != allocd) {
      size_type old_size = this->size();
      iterator new_v = new value_type[size];
      if (!empty()) {
        copy_contents(new_v, start, old_size);
      }
      delete[] start;
      start = new_v;
      allocd = size;
      finish = start + old_size;
    }
  }
  size_type capacity() const noexcept { return allocd; }
  void shrink_to_fit() { reserve(size()); }

  // vector modifiers
  void clear() noexcept { finish = start; }
  iterator insert(iterator pos, const_reference value) {
    size_type offset = pos - start;
    push_back(value_type());
    for (iterator p = finish - 2; p >= start + offset; --p) {
      p[1] = p[0];
    }
    start[offset] = value;
    return start + offset;
  }
  void erase(iterator pos) noexcept {
    for (iterator p = pos; p < finish - 1; ++p) {
      p[0] = p[1];
    }
    pop_back();
  }
  void push_back(const_reference value) {
    if (allocd == size()) {
      reserve_push_back();
    }
    finish[0] = value;
    ++finish;
  }
  void pop_back() noexcept {
    if (!empty()) {
      --finish;
    }
  }
  void swap(vector &other) noexcept {
    iterator temp = start;
    start = other.start;
    other.start = temp;
    temp = finish;
    finish = other.finish;
    other.finish = temp;
    size_t tempsize = allocd;
    allocd = other.allocd;
    other.allocd = tempsize;
  }
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_t offset = pos - start;
    reserve(size() + sizeof...(args));
    iterator it = start + offset;
    size_t i = 0;
    for (auto &&arg : {args...}) {
      insert(it + i, arg);
      ++i;
    }
    return it;
  }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    reserve(size() + sizeof...(args));
    for (auto &&arg : {args...}) {
      push_back(arg);
    }
  }

 private:
  iterator start;
  iterator finish;
  size_type allocd;

  void null() noexcept {
    start = nullptr;
    finish = nullptr;
    allocd = 0;
  }
  void reserve_push_back() {
    if (allocd == 0) {
      reserve(1);
    } else if (allocd == 1) {
      reserve(2);
    } else {
      reserve(size() + size() / 2);
    }
  }
  void copy_contents(iterator dest, iterator src, size_type count) noexcept {
    for (size_type i = 0; i < count; ++i) {
      dest[i] = src[i];
    }
  }
};
}  // namespace s21

#endif  // S21_CONTAINERS_S21_VECTOR_VECTOR_H_
