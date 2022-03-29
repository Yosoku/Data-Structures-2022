#ifndef PAIR_FREQUENCY_H
#define PAIR_FREQUENCY_H

#include <ostream>
#include <string>
class PairFrequency {
 public:
  PairFrequency() = delete;
  PairFrequency(const std::string&, const std::string&);
  ~PairFrequency();
  void IncrementFrequency();
  friend std::ostream& operator<<(std::ostream& os, const PairFrequency& pf);
  bool operator==(const PairFrequency& other) const;
  bool operator<(const PairFrequency& other) const;
  bool operator>(const PairFrequency& other) const;

 private:
  std::string word1, word2;
  unsigned int frequency;
};

#endif  // PAIR_FREQUENCY_H