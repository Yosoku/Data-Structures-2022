#ifndef HASHSET_H
#define HASHSET_H
#include <string.h>  // memset

#include <cmath>
#include <cstddef>       //std::size_t
#include <iostream>      // std::ostream
#include <new>           // ::operator new/delete
#define kTolerance 0.75  // Resize is triggered at 75% capacity
namespace ds {

template <typename T>
class Hashset {
 public:
  // Default constructor sets the initial capacity to 10 and every character in
  // the flag array to empty('E'). Tolerance is set at the default value 75%
  Hashset() : size_(0), capacity_(10) {
    buffer_ = (T*)::operator new(capacity_ * sizeof(T));
    flags = new char[capacity_];
    memset(flags, 'E', capacity_);
    tolerance = kTolerance;
  }
  // Overloaded constructor sets the initial capacity to initialCapacity and
  // every character in the flag array to empty('E').Tolerance is set at the
  // default value 75%
  Hashset(std::size_t initialCapacity) : size_(0), capacity_(initialCapacity) {
    buffer_ = (T*)::operator new(capacity_ * sizeof(T));
    flags = new char[capacity_];
    memset(flags, 'E', capacity_);
    tolerance = kTolerance;
  }

  // Overloaded constructor sets the initial capacity and the tolerance  as well
  // as every character in the flag array to empty('E').
  Hashset(std::size_t initialCapacity, float tol)
      : size_(0), capacity_(initialCapacity), tolerance(tol) {
    buffer_ = (T*)::operator new(capacity_ * sizeof(T));
    flags = new char[capacity_];
    memset(flags, 'E', capacity_);
  }

  // Returns true if the hashset is empty (buffer has no elements)
  inline constexpr bool IsEmpty() const { return size_ == 0; }

  // Returns the size of the hashset(number of elements in the buffer)
  inline constexpr std::size_t Size() const { return size_; }

  // Returns the size of the hashset(number of elements in the buffer)
  inline constexpr std::size_t Length() const { return size_; }

  // Returns the space allocated in the buffer
  inline constexpr std::size_t Capacity() const { return capacity_; }

  // Add method
  // Method may call resize() if the load factor exceeds the default TOLERANCE
  // Runs in O(n) time
  void Add(const T& element) {
    if (size_ * 1.0 / capacity_ > tolerance) Resize();
    std::size_t index = GetBucket(element);
    if (index == -1) return;  // duplicate value
    flags[index] = 'O';       // O = Occupied
    new (buffer_ + index) T(element);
    size_++;
  }

  // Add method with move semantics similiar to Add(const T&)
  // Method may call resize() if the load factor exceeds the default TOLERANCE
  // Runs in O(n) time
  void Add(T&& element) {
    std::cout << "In add for " << element << '\n';
    if (size_ * 1.0 / capacity_ > tolerance) Resize();
    std::size_t index = GetBucket(element);
    if (index == -1) return;  // duplicate value
    flags[index] = 'O';
    new (buffer_ + index) T(std::move(element));
    size_++;
  }

  // Python style printing
  // Prints the hashset as well as the flag array
  friend std::ostream& operator<<(std::ostream& os, const Hashset<T>& set) {
    os << '[';
    if (set.flags[0] == 'O')
      os << set.buffer_[0] << ',';
    else
      os << set.flags[0] << ',';
    for (std::size_t i = 1; i < set.capacity_ - 1; ++i) {
      if (set.flags[i] == 'O')
        os << set.buffer_[i];
      else
        os << set.flags[i];
      os << ',';
    }
    if (set.flags[set.capacity_ - 1] == 'O')
      os << set.buffer_[set.capacity_ - 1] << ']';
    else
      os << set.flags[set.capacity_ - 1] << ']';

    os << "\nFlags\n";
    for (std::size_t i = 0; i < set.capacity_; ++i) {
      os << set.flags[i] << ',';
    }
    os << '\n';
    return os;
  }

  // Contais returns a pair<bool,std::size_t> where pair.first is the result of
  // the search and pair.second is the index where the element lives in the
  // buffer. This is useful for searching elements externally and deleting them
  // itnernally. The search continues while the flag is Occupied or Deleted
  std::pair<bool, std::size_t> Contains(const T& element) const {
    std::size_t index = hashcode(element, 0);
    std::size_t count = 1;
    while (flags[index] != 'E') {
      if (buffer_[index] == element && flags[index] != 'D') {
        return {true, index};
      }  // duplicate value
      index = hashcode(element, count);
      count++;
    }
    return {false, -1};  // Index -1 since element doesnt exist in the buffer
  }

  // Remove searches for the element in the buffer using Contains(const T&).If
  // the element is found Remove sets the flag of the element in the buffer as
  // 'D' = Deleted and calls the destructor of T. If the element is not found
  // the method exits without changing the buffer.
  void Remove(const T& element) {
    std::pair<bool, std::size_t> result = Contains(element);
    if (!result.first)  // Not found
      return;
    std::size_t index = result.second;
    buffer_[index].~T();
    flags[index] = 'D';
    std::cout << buffer_[index] << '\n';
  }

 private:
  // The hash method  Using std::hash
  // Its important that the templated arguement T has an overload for std::hash
  // to avoid 600 pages of C++ style unreadable compile errors
  inline std::size_t hashcode(const T& element, std::size_t col) const {
    return (std::hash<T>()(element) * 0x7fffffff + col * col) % capacity_;
  }

  // GetBucket is used to find the index mapping to the element when inserting.
  // Returns the bucket that the element belongs to in the buffer,-1 in case of
  // duplicate values
  std::size_t GetBucket(const T& element) {
    std::size_t index = hashcode(element, 0);
    std::size_t count = 1;
    while (flags[index] == 'O')  // collision
    {
      if (buffer_[index] == element) return -1;  // duplicate value
      index = hashcode(element, count);
      count++;
    }
    return index;
  }

  // Overload of GetBucket that is a helper method to Resize() which takes a
  // buffer and flags array to find the bucket
  std::size_t GetBucket(const T& element, T* buffer_, char* flags) {
    std::size_t index = hashcode(element, 0);
    std::size_t count = 1;
    while (flags[index] == 'O')  // collision
    {
      if (buffer_[index] == element) return -1;  // duplicate value
      index = hashcode(element, count);
      count++;
    }
    return index;
  }
  // Resize method gets called if the load factor exceeds the tolerance (default
  // 75%). Resize doubles the buffer capacity and rehashes every element. Its
  // preferable to avoid resizing as much as possible. If capacity is known at
  // compile time it should be set to max. Method also resizes the flag array.
  void Resize() {
    std::size_t oldCapacity = capacity_;
    capacity_ <<= 1;
    T* newBlock = (T*)::operator new(capacity_ * sizeof(T));
    char* newFlags = new char[capacity_];
    memset(newFlags, 'E', capacity_);
    for (std::size_t i = 0; i < oldCapacity; i++) {
      if (flags[i] == 'O') {
        std::size_t index = GetBucket(buffer_[i], newBlock, newFlags);
        new (newBlock + index) T(std::move(buffer_[i]));
        newFlags[index] = 'O';
      }
    }
    for (std::size_t i = 0; i < size_; i++) buffer_[i].~T();
    ::operator delete(buffer_, oldCapacity * sizeof(T));
    delete[] flags;
    flags = newFlags;
    buffer_ = newBlock;
  }

  T* buffer_ = nullptr;
  char* flags;  // Flags have 3 states : O for Occupied,
                // E for empty,D for deleted
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  float tolerance = 0.75;  // The buffer will reach 75% capacity before resizing
};
};      // namespace ds
#endif  // HASHSET_H
