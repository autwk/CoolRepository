#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <string>

class RationalDivisionByZero : public std::exception {};

int32_t GCD(int32_t a, int32_t b);

class Rational {
 private:
  int32_t p_ = 0;
  int32_t q_ = 1;

 public:
  Rational();
  Rational(int32_t p, int32_t q);  // NOLINT
  Rational(int32_t p);             // NOLINT
  Rational(const Rational& r);
  void Reduce();
  int32_t GetNumerator() const;
  int32_t GetDenominator() const;
  void SetNumerator(int32_t p);
  void SetDenominator(int32_t q);
  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);

  Rational& operator++();
  Rational operator++(int32_t);

  Rational& operator--();
  Rational operator--(int32_t);
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