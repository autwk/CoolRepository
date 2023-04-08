#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <iostream>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t N>
class Array {
 public:
  T arr[N];

  T& operator[](size_t pos) {
    return arr[pos];
  }

  const T& operator[](size_t pos) const {
    return arr[pos];
  }

  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }

    return arr[idx];
  }

  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }

    return arr[idx];
  }

  T& Front() {
    return arr[0];
  }

  const T& Front() const {
    return arr[0];
  }

  T& Back() {
    return arr[N - 1];
  }

  const T& Back() const {
    return arr[N - 1];
  }

  T* Data() noexcept {
    return arr;
  }

  const T* Data() const noexcept {
    return arr;
  }

  size_t Size() const noexcept {
    return N;
  }

  bool Empty() const noexcept {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = value;
    }
  }

  void Swap(Array<T, N>& other) noexcept {
    std::swap(this->arr, other.arr);
  }
};

#endif
