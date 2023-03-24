#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <string>

class RationalDivisionByZero : public std::exception {};

int GCD(int a, int b);

class Rational {
 public:
  Rational();
  Rational(int p, int q);  // NOLINT
  Rational(int p);         // NOLINT
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

 private:
  int p_ = 0;
  int q_ = 1;
  void Reduce();
};

Rational operator+(Rational copy);
Rational operator-(Rational copy);

Rational operator+(const Rational& first, const Rational& second);
Rational operator-(const Rational& first, const Rational& second);
Rational operator*(const Rational& first, const Rational& second);
Rational operator/(const Rational& first, const Rational& second);

bool operator<(const Rational& first, const Rational& second);
bool operator>(const Rational& first, const Rational& second);
bool operator<=(const Rational& first, const Rational& second);
bool operator>=(const Rational& first, const Rational& second);
bool operator==(const Rational& first, const Rational& second);
bool operator!=(const Rational& first, const Rational& second);

std::ostream& operator<<(std::ostream& os, const Rational& val);
std::istream& operator>>(std::istream& is, Rational& val);

#endif