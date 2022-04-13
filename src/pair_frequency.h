#ifndef PAIR_FREQUENCY_H
#define PAIR_FREQUENCY_H

#include <cstddef>
#include <functional>
#include <ostream>
#include <string>
class PairFrequency {
 public:
  PairFrequency() = default;
  PairFrequency(const std::string&, const std::string&);
  ~PairFrequency();
  void IncrementFrequency();
  friend std::ostream& operator<<(std::ostream& os, const PairFrequency& pf);
  bool operator==(const PairFrequency& other) const;
  bool operator<(const PairFrequency& other) const;
  bool operator>(const PairFrequency& other) const;
  std::string GetWord1() const { return word1; }
  std::string GetWord2() const { return word2; }

 private:
  std::string word1, word2;
  unsigned int frequency;
};
namespace std {
template <>
struct hash<PairFrequency> {
  size_t operator()(const PairFrequency& pf) {
    return std::hash<std::string>()(pf.GetWord1() + pf.GetWord2());
  }
};
};  // namespace std

#endif  // PAIR_FREQUENCY_H