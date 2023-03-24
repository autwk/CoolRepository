#include "rational.h"

int GCD(int a, int b) {
  if (b == 0) {
    return a;
  }

  a %= b;
  return GCD(b, a);
}

Rational::Rational() = default;

Rational::Rational(int p, int q) {  // NOLINT
  if (q == 0) {
    throw RationalDivisionByZero();
  }

  p_ = p;
  q_ = q;
  Reduce();
}

Rational::Rational(int p) {  // NOLINT
  p_ = p;
  q_ = 1;
}

Rational::Rational(const Rational& r) {
  p_ = r.p_;
  q_ = r.q_;
}

void Rational::Reduce() {
  int gcd = GCD(p_, q_);
  p_ /= gcd;
  q_ /= gcd;

  if (q_ < 0) {
    q_ = -q_;
    p_ = -p_;
  }
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int p) {
  p_ = p;
  Reduce();
}

void Rational::SetDenominator(int q) {
  if (q == 0) {
    throw RationalDivisionByZero();
  }

  q_ = q;
  Reduce();
}

Rational& Rational::operator+=(const Rational& other) {
  p_ = p_ * other.q_ + q_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  p_ = p_ * other.q_ - q_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  p_ = p_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (other.p_ == 0) {
    throw RationalDivisionByZero();
  }

  p_ = p_ * other.q_;
  q_ = q_ * other.p_;
  Reduce();
  return *this;
}

Rational& Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

Rational operator+(Rational copy) {
  return copy;
}

Rational operator-(Rational copy) {
  copy.SetNumerator(-copy.GetNumerator());
  return copy;
}

Rational operator+(const Rational& first, const Rational& second) {
  Rational copy = first;
  copy += second;
  return copy;
}

Rational operator-(const Rational& first, const Rational& second) {
  Rational copy = first;
  copy -= second;
  return copy;
}

Rational operator*(const Rational& first, const Rational& second) {
  Rational copy = first;
  copy *= second;
  return copy;
}

Rational operator/(const Rational& first, const Rational& second) {
  if (second.GetNumerator() == 0) {
    throw RationalDivisionByZero();
  }

  Rational copy = first;
  copy /= second;
  return copy;
}

bool operator<(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator();
}

bool operator>(const Rational& first, const Rational& second) {
  return second < first;
}

bool operator<=(const Rational& first, const Rational& second) {
  return !(first > second);
}

bool operator>=(const Rational& first, const Rational& second) {
  return !(first < second);
}

bool operator==(const Rational& first, const Rational& second) {
  return !(first < second) && !(second < first);
}

bool operator!=(const Rational& first, const Rational& second) {
  return !(first == second);
}

std::ostream& operator<<(std::ostream& os, const Rational& val) {
  if (val.GetDenominator() == 1) {
    os << val.GetNumerator();
  } else {
    os << val.GetNumerator() << '/' << val.GetDenominator();
  }
  return os;
}

std::istream& operator>>(std::istream& is, Rational& val) {
  int p = 0, q = 0;
  bool p_minus_flag = false, q_minus_flag = false, is_slash_flag = false;
  std::string in;
  is >> in;
  int size = in.size();
  for (int i = 0; i < size; ++i) {
    char temp = in[i];

    if (temp == '/') {
      is_slash_flag = true;
    } else if (temp == '-') {
      if (is_slash_flag) {
        q_minus_flag = true;
      } else {
        p_minus_flag = true;
      }
    } else if ('0' <= temp && temp <= '9') {
      if (is_slash_flag) {
        q *= 10;
        q += in[i] - '0';
      } else {
        p *= 10;
        p += in[i] - '0';
      }
    }
  }

  p = (p_minus_flag) ? -p : p;
  q = (q_minus_flag) ? -q : q;
  val.SetNumerator(p);

  if (is_slash_flag) {
    val.SetDenominator(q);
  }

  return is;
}
