#ifndef ARRAY_H
#define ARRAY_H
#include <time.h>  //time

#include <cassert>   // assert
#include <cstdint>   //uint
#include <cstdlib>   //rand
#include <iostream>  // std::ostream
#include <new>       // operator new,delete
#include <utility>   //std::swap
namespace ds {

// Array class represents a dynamic unsorted array which supports
// insertion,deletion,search and sorting. If the Array reaches maximum capacity
// then the resize() method doubles the capacity.

template <typename T>
class Array {
 public:
  // Default constructor creates an initial capacity of 2 and allocates memory
  // for the buffer

  Array() : capacity_(2), size_(0) {
    buffer_ = (T*)::operator new(capacity_ * sizeof(T));
  }
  // constructor which creates an initial capacity of n and allocates memory
  // for the buffer. Useful in cases where optimization is key e.g. if you know
  // you will add >1.000.000 elements and you call Array(1000000) then Resize
  // will not be called. Same example with Array() will call Resize 20
  // times,resulting in an unwanted overhead

  Array(int n) : capacity_(n), size_(0) {
    buffer_ = (T*)::operator new(capacity_ * sizeof(T));
  }

  // Copy constructor for deep copying an Array
  Array(const Array& other) : capacity_(other.capacity_), size_(other.size_) {
    buffer_ = new T[capacity_];
    for (int i = 0; i < other.size_; ++i) {
      buffer_[i] = other.buffer_[i];
    }
  }
  ~Array() {
    Clear();  // calls the destructors of each element
    ::operator delete(buffer_, capacity_ * sizeof(T));
    size_ = capacity_ = 0;
  }

  // Size returns the number of elements that buffer_ contains, __NOT__ the
  // capacity of the buffer_
  // e.g Array [1,2,3,4] has a size_ of 4,but capacity could be
  // any uint64_t  number
  inline int Size() const noexcept { return size_; }
  // Length is just the Size() method but more intuitive,
  // following C++ conventions
  inline int Length() const noexcept { return size_; }

  // Capacity returns the maximum number of elements that the Array can fit in
  // the given moment
  inline int Capacity() const noexcept { return capacity_; };

  // Returns true if the Array is empty and has no elements,false otherwise
  inline bool IsEmpty() const noexcept { return size_ == 0; }

  // Clears all elements from the buffer by calling their destructor and setting
  // the final size to 0,capacity remains untouched
  void Clear() {
    for (int i = 0; i < size_; ++i) buffer_[i].~T();
    size_ = 0;
  }

  inline T& At(uint64_t index) const {
    assert((index < size_) && (index >= 0) && "Index out of bounds");
    return buffer_[index];
  }
  // Inserts element in the end of the Array,similar to
  // std::vector.push_back(element). If the array is full the method
  // makes a Resize() call to resize the array to twice the size(Overhead)
  // Time complexity of O(size_),initialize the Array with a big enough size
  // to keep Time complexity at Omega(1)
  virtual void Add(const T& element) {
    if (size_ >= capacity_)  // array full
      Resize(capacity_ + (capacity_ >> 1) + 1);
    buffer_[size_++] = std::move(element);
  }

  virtual void Add(T&& element) {
    if (size_ >= capacity_)  // array full
      Resize(capacity_ + (capacity_ >> 1) + 1);
    new (buffer_ + size_++) T(std::move(element));
  }

  // Returns true if element is present in Array,false otherwise. Using linear
  // search since the Array is unordered the Time Complexity is stuck at
  // O(size_). Sorting the Array will
  // not lower the overhead since the API doesn't provide any other
  // implementation of Contains that uses binary search
  virtual bool Contains(const T& element) const {
    for (int i = 0; i < size_; ++i) {
      if (element == buffer_[i]) return true;
    }
    return false;
  }
  // Returns the index if element is present in Array,-1 otherwise. Using linear
  // search since the Array is unordered the Time Complexity is stuck at
  // O(size_). Sorting the Array will
  // not lower the overhead since the API doesn't provide any other
  // implementation of Contains that uses binary search
  virtual int Search(const T& element) const {
    for (int i = 0; i < size_; ++i) {
      if (element == buffer_[i]) return i;
    }
    return -1;
  }
  // Removes element if found and returns true,false otherwise. Using linear
  // search to locate the element since the Array remains unordered in run time.
  // Time complexity of O(n),Sorting the Array will
  // not lower the overhead since the API doesn't provide any other
  // implementation of Contains
  virtual bool Remove(const T& element) {
    for (int i = 0; i < size_; ++i) {
      if (buffer_[i] == element) {
        buffer_[i].~T();
        for (int j = i; j < size_ - 1; ++j) {
          buffer_[j] = std::move(
              buffer_[j + 1]);  // shift elements left after deleted element
        }
        size_--;
        return true;
      }
    }
    return false;
  }
  // Rearranges the Array in random order. Helper method for using Array in
  // combination with other Data structures
  void Shuffle() {
    srand(time(nullptr));
    int rand1, rand2;
    for (int i = 0; i < 100; ++i) {
      rand1 = rand() % size_;
      rand2 = rand() % size_;
      std::swap(buffer_[rand1], buffer_[rand2]);
    }
  }
  // Operator overloads
  T& operator[](int index) {
    assert((index < size_) && (index >= 0) && "Index out of bounds");
    return buffer_[index];
  }
  const T& operator[](int index) const {
    assert((index < size_) && (index >= 0) && "Index out of bounds");
    return buffer_[index];
  }

  // Python-style printing
  friend std::ostream& operator<<(std::ostream& os, const Array& ar) {
    if (ar.size_ <= 0) {
      os << "[]";
      return os;
    }
    os << '[';
    os << ar.buffer_[0] << ',';
    for (int i = 1; i < ar.size_ - 1; ++i) {
      os << ar.buffer_[i] << ',';
    }
    os << ar.buffer_[ar.size_ - 1] << ']';
    return os;
  }

 protected:
  void Resize(uint64_t newCapacity) {
    T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
    for (uint64_t i = 0; i < size_; i++)
      new (newBlock + i) T(std::move(buffer_[i]));
    for (uint64_t i = 0; i < size_; i++) buffer_[i].~T();
    ::operator delete(buffer_, capacity_ * sizeof(T));
    buffer_ = newBlock;
    capacity_ = newCapacity;
  }

 protected:
  T* buffer_ = nullptr;
  uint64_t size_ = 0;
  uint64_t capacity_ = 0;
};
}  // namespace ds
#endif  // ARRAY_H
