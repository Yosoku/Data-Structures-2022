#ifndef QUEUE_H
#define QUEUE_H
#include <cstdint>
#include <new>

#include "array.hpp"
namespace ds {

template <typename T>
class Queue : public ds::Array<T> {
 public:
  // Pushes an element in the front of the queue
  // Runs in O(n)
  void Push(const T& element) { ds::Array<T>::Add(element); }

  // Returns the front of the queue
  // Runs in O(1)
  T& Front() { return this->buffer_[0]; }
  // const overload of Front
  const T& Front() const { return this->buffer_[0]; }

  // Deletes the element in the front of the queue and shifts all elements left
  // Runs in O(n)
  void Pop() {
    this->buffer_[0].~T();
    for (int i = 0; i < this->size_; ++i) {
      this->buffer_[i] = std::move(this->buffer_[i + 1]);
    }
    this->size_--;
  }
};

};      // namespace ds
#endif  // QUEUE_H