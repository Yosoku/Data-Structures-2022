#ifndef SORTED_ARRAY_H
#define SORTED_ARRAY_H

#include "array.hpp"
namespace ds {

template <typename T>
class OrderedArray : public Array<T> {
 public:
  // Inserts element while keeping ascending order. Shifts all the elements
  // right. If needed this method will call Resize() to reallocate more memory
  // for the buffer. Runs in O(n)
  void Add(const T& element) override {
    printf("normal add\n");
    if (this->size_ >= this->capacity_)  // array full
      this->Resize(this->capacity_ + (this->capacity_ >> 1) + 1);
    int i;
    for (i = this->size_ - 1; (i >= 0 && this->buffer_[i] > element); i--)
      this->buffer_[i + 1] = this->buffer_[i];
    new (this->buffer_ + i + 1) T(std::move(element));
    this->size_++;
  }

  void Add(T&& element) override {
    if (this->size_ >= this->capacity_)  // array full
      this->Resize(this->capacity_ + (this->capacity_ >> 1) + 1);
    int i;
    for (i = this->size_ - 1; (i >= 0 && this->buffer_[i] > element); i--)
      this->buffer_[i + 1] = this->buffer_[i];
    new (this->buffer_ + i + 1) T(std::move(element));
    this->size_++;
  }

  // Returns the index of element if found,-1 otherwise. This method uses binary
  // search and Runs in O(logn) time
  int Search(const T& element) const override {
    int low = 0, high = this->size_ - 1, mid;
    while (low <= high) {
      mid = low + (high - low) / 2;
      if (this->buffer_[mid] == element) return mid;
      if (this->buffer_[mid] < element) low = mid + 1;
      if (this->buffer_[mid] > element) high = mid - 1;
    }
    return -1;
  }
  // Finds the element index and deletes it if found.Returns true if
  // deleted,false otherwise. This method uses binary search to find the element
  // and then shifts the array left. Runs in O(n) time
  bool Remove(const T& element) override {
    int index = Search(element);
    if (index == -1) return false;
    this->buffer_[index].~T();
    for (int i = index; i < this->size_; ++i) {
      this->buffer_[i] = this->buffer_[i + 1];
    }
    this->size_--;
    return true;
  }

  // Returns true if element is present in the array,false otherwise. Runs in
  // O(logn) time
  bool Contains(const T& element) const override {
    return Search(element) != -1;
  }
};
}  // namespace ds
#endif  // SORTED_ARRAY_H