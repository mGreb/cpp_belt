#pragma once
// system includes
#include <cstdlib>
#include <cmath>

template <typename T>
class SimpleVector {
public:
  SimpleVector() {
    data = nullptr;
    size = 0;
    capacity = 0;
  }
  
  explicit SimpleVector(size_t size_) : size(size_) {
    capacity = 1 << (size_t)std::ceil(std::log(size) + 1);
    data = new T[capacity];
  }
  
  ~SimpleVector() {
    delete[] data;
  }
  
  T& operator[](size_t index) {
    return data[index];
  }
  const T& operator[](size_t index) const {
    return data[index];
  }
  
  T* begin() {
    return data;
  }
  const T* begin() const {
    return data;
  }
  
  T* end() {
    return data + size;
  }
  const T* end() const {
    return data + size;
  }
  
  [[nodiscard]]
  size_t Size() const {
    return size;
  }
  [[nodiscard]]
  size_t Capacity() const {
    return capacity;
  }
  
  void PushBack(const T& value) {
    if (capacity == 0) {
      capacity = 1;
      size = 0;
      data = new T[capacity];
    }
    if (size == capacity) {
      capacity *= 2;
      T* new_data = new T[capacity];
      for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
      }
      delete[] data;
      data = new_data;
    }
    data[size] = value;
    ++size;
  }
  
private:
  T* data;
  size_t size;
  size_t capacity;
};
