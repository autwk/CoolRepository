#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <string>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

int GCD(int a, int b);

class Rational {
  private:
  int p_ = 0;
  int q_ = 1;

  public:
  void Reduce();
  Rational();
  Rational(int p);         // NOLINT
  Rational(int p, int q);  // NOLINT
  Rational(const Rational& r);
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int p);
  void SetDenominator(int q);
  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);

  Rational& operator++();
  Rational operator++(int);

  Rational& operator--();
  Rational operator--(int);
};
Rational operator+(Rational copy);
Rational operator-(Rational copy);
Rational operator+(const Rational& first, const Rational& other);
Rational operator-(const Rational& first, const Rational& other);
Rational operator*(const Rational& first, const Rational& other);
Rational operator/(const Rational& first, const Rational& other);
bool operator<(const Rational& f, const Rational& s);
bool operator>(const Rational& f, const Rational& s);
bool operator<=(const Rational& f, const Rational& s);
bool operator>=(const Rational& f, const Rational& s);
bool operator==(const Rational& f, const Rational& s);
bool operator!=(const Rational& f, const Rational& s);
std::ostream& operator<<(std::ostream& os, const Rational& val);
std::istream& operator>>(std::istream& is, Rational& val);
#endif