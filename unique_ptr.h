#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <iostream>

template <typename T>
class UniquePtr {
 public:
  UniquePtr() : ptr_(nullptr) {
  }

  explicit UniquePtr(T* other) : ptr_(other) {
  }

  UniquePtr(const UniquePtr<T>&) = delete;

  UniquePtr& operator=(const UniquePtr<T>&) = delete;

  UniquePtr(UniquePtr&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    Reset(other.ptr_);
    other.ptr_ = nullptr;
    return *this;
  }

  T* Release() {
    T* copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }

  void Reset(T* ptr = nullptr) {
    if (ptr_ != ptr) {
      delete ptr_;
    }

    ptr_ = ptr;
  }

  void Swap(UniquePtr<T>& other) {
    std::swap(ptr_, other.ptr_);
  }

  T* Get() const {
    return ptr_;
  }

  T& operator*() const {
    return *Get();
  }

  T* operator->() const {
    return Get();
  }

  explicit operator bool() const {
    return Get() != nullptr;
  }

  ~UniquePtr() {
    Reset();
  }

 private:
  T* ptr_;
};
#endif
