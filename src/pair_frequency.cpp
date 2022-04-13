#include "pair_frequency.h"

std::ostream& operator<<(std::ostream& os, const PairFrequency& pf) {
  os << '(' << pf.word1 << ',' << pf.word2 << ") : " << pf.frequency << '\n';
  return os;
}

bool PairFrequency::operator==(const PairFrequency& other) const {
  return word1.compare(other.word1) == 0 && word2.compare(other.word2) == 0;
}

bool PairFrequency::operator<(const PairFrequency& other) const {
  int cmp = word1.compare(other.word1);
  if (cmp) return cmp < 0;
  return word2.compare(other.word2) < 0;
}

bool PairFrequency::operator>(const PairFrequency& other) const {
  return other.operator<(*this);
}
PairFrequency::PairFrequency(const std::string& w1, const std::string& w2)
    : word1(w1), word2(w2), frequency(1) {}

PairFrequency::~PairFrequency() {
  word1 = word2 = "";
  frequency = 0;
}

void PairFrequency::IncrementFrequency() { frequency++; }