#include "pair_frequency.h"

std::ostream& operator<<(std::ostream& os, const PairFrequency& pf) {
  os << '(' << pf.word1 << ',' << pf.word2 << ") : " << pf.frequency << '\n';
  return os;
}

bool PairFrequency::operator==(const PairFrequency& other) const {
  return (word1 == other.word1 && word2 == other.word2);
}

bool PairFrequency::operator<(const PairFrequency& other) const {
  return word1 < other.word1;
}

bool PairFrequency::operator>(const PairFrequency& other) const {
  return this->operator<(other);
}
PairFrequency::PairFrequency(const std::string& w1, const std::string& w2)
    : word1(w1), word2(w2), frequency(1) {}

PairFrequency::~PairFrequency() {
  word1 = word2 = "";
  frequency = 0;
}

void PairFrequency::IncrementFrequency() { frequency++; }