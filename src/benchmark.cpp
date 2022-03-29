#include "benchmark.h"

void TotalMemoryUsage() {
  printf("Memory usage : %d bytes\n",
         bmark::allocated_bytes__ - bmark::freed_bytes__);
}
void* operator new(size_t bytes) {
  bmark::allocated_bytes__ += bytes;
  TotalMemoryUsage();
  return malloc(bytes);
}
void operator delete(void* memory_block, size_t bytes) {
  bmark::freed_bytes__ += bytes;
  TotalMemoryUsage();
  free(memory_block);
}
bmark::Timer::Timer() { start = high_resolution_clock::now(); }
bmark::Timer::~Timer() {
  end = high_resolution_clock::now();
  duration<double> duration1 = end - start;
  printf("Timer took %f ms\n", duration1.count() * 1000.0f);
}