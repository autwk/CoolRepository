#include "rational.h"

int GCD(int a , int b) {
   if (b == 0) {
    return a;
   }
   a %= b;
   return GCD(b,a);
}

Rational::Rational(int p, int q) { // NOLINT
  if (q == 0) {
    throw RationalDivisionByZero();
  }
  p_ = p;
  q_ = q;
  Reduce();
  if (q < 0) {
    q_ = -q;
    p_ = -p;
  }
}
Rational::Rational(int p) { // NOLINT
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
  this->p_ = p;
  Reduce();
}
void Rational::SetDenominator(int q) {
  if (q != 0) {
    this->q_ = q;
  } else {
    throw RationalDivisionByZero();
  }
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
Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}
Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}
Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}
Rational operator/(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy /= other;
  return copy;
}

bool operator<(const Rational& f, const Rational& s) {
  return f.GetNumerator() * s.GetDenominator() < f.GetDenominator() * s.GetNumerator();
}
bool operator>(const Rational& f, const Rational& s) {
  return s < f;
}
bool operator<=(const Rational& f, const Rational& s) {
  return !(f > s);
}
bool operator>=(const Rational& f, const Rational& s) {
  return !(f < s);
}
bool operator==(const Rational& f, const Rational& s) {
  return !(f < s) && !(s < f);
}
bool operator!=(const Rational& f, const Rational& s) {
  return !(f == s);
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
  bool p_minus = false, q_minus = false, slash = false;
  std::string in;
  std::cin >> in;
  for (int i = 0; i < in.size(); ++i) {
    char temp = in[i];
    if (temp == '/') {
      slash = true;
    } else if (temp == '-') {
      if (slash) {
        q_minus = true;
      } else {
        p_minus = true;
      }
    } else {
      if (slash) {
        q *= 10;
        q += in[i] - '0';
      } else {
        p *= 10;
        p += in[i] - '0';
      }
    }
  }
  p = (p_minus) ? -p : p;
  q = (q_minus) ? -q : q;
  if (!slash) {
    val.SetNumerator(p);
  } else {
    val.SetNumerator(p);
    val.SetDenominator(q);
  }
  val.Reduce();
  return is;
}