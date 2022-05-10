#pragma once

// system includes
#include <stdexcept>
#include <array>

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) : size(a_size) {
    if (size > N)
      throw std::invalid_argument("");
  }
  
  T& operator[](size_t index) {
    return data[index];
  }
  const T& operator[](size_t index) const {
    return data[index];
  }
  
  T* begin() {
    return &data[0];
  }
  T* end() {
    return &data[0] + size;
  }
  const T* begin() const {
    return &data[0];
  }
  const T* end() const {
    return &data[0] + size;
  }
  
  size_t Size() const {
    return size;
  }
  size_t Capacity() const {
    return data.size();
  }
  
  void PushBack(const T& value) {
    if (size == data.size())
      throw std::overflow_error("");
    else
      data[size++] = value;
  }
  T PopBack() {
    if (size == 0)
      throw std::underflow_error("");
    return data[(size--) - 1];
  }
  
private:
  std::array<T, N> data;
  size_t size;
};
