#include <iostream>

class Fraction {
private:
  int m_nominator{0};
  int m_denominator{1};

public:
  Fraction(int nominator = 0, int denominator = 1)
      : m_nominator(nominator), m_denominator(denominator) {}

  friend std::ostream &operator<<(std::ostream &out, const Fraction &f1) {
    return out << f1.m_nominator << '/' << f1.m_denominator;
  }
};
class Resource_1 {
public:
  std::weak_ptr<Resource_1>
      m_ptr{}; // use std::weak_ptr so m_ptr doesn't keep the Resource alive

  Resource_1() { std::cout << "Resource acquired\n"; }
  ~Resource_1() { std::cout << "Resource destroyed\n"; }
};