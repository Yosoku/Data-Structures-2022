#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <memory>

void operator delete(void* memory_block, size_t bytes);
void* operator new(size_t bytes);
namespace bmark {
inline uint32_t allocated_bytes__ = 0, freed_bytes__ = 0;
void TotalMemoryUsage();
using namespace std::chrono;
struct Timer {
  system_clock::time_point start, end;
  Timer();
  ~Timer();
};

};      // namespace bmark
#endif  // BENCHMARK_HPP