#include "Mod.h"
#include <climits>

/*
 * Robert Kim
 * September 21st, 2015
 * Modulus Lab
 */

Mod::Mod(long t) {
    long r = t % modulus;
    x = ((r < 0) ? r + modulus : r);
}

Mod::Mod(const Mod& m) {
    x = m.val();
}

Mod& Mod::operator=(const Mod& m) {
    x = m.val();
    return *this;
}

Mod& Mod::operator+=(const Mod& m) {
    *this = (x + m.val() - modulus);
    return *this = x + (x < 0 ? modulus : 0);
}

Mod& Mod::operator-=(const Mod& m) {
    return *this += -m;
}

Mod& Mod::operator*=(const Mod& m) {
    if (m.val() == 0) return *this = 0;
    if (x == 0) return *this;
    long mult = m.val();
    Mod temp(0);
    for (long mult = m.val(); mult > 0; mult /= 2) {
        if (mult % 2 != 0) temp += *this;
        *this += *this;
    }
    x = temp.val();
    return *this;
}

Mod& Mod::operator/=(const Mod& m) {
    return *this *= inv(m.val());
}

Mod Mod::operator-() const {
    return Mod(modulus - x);
}

Mod Mod::pwr(long e) const {
    if (e < 0) return inv(x).pwr(-e);
    if (e == 0) return Mod(1);

    Mod result(x);
    Mod temp(1);
    for (long expo = e; expo > 0; expo /= 2) {
        if (expo % 2 == 1) temp *= result;
        result *= result;
    }
    result = temp.val();
    return result;
}

long Mod::val() const {
    return x;
}

void Mod::set_modulus(long m) {
    assert(m >= 2);
    modulus = m;
}

Mod Mod::inv(long r0) {
    assert(r0 != 0);
    long v = r0, a = modulus, temp, q, x = 0, lx = 1;
    if (a == 1) return 1;
    while (v > 1) {
        q = v / a;
        temp = a;
        a = v % a;
        v = temp;
        
        temp = x;
        x = lx - q * x;
        lx = temp;
    }
    if (lx < 0) lx += modulus;
    assert(v == 1);
    return Mod(lx);
}

Mod operator+(const Mod& a, const Mod& b) {
    return Mod(a) += b;
}

Mod operator+(long t, Mod& m) {
    return Mod(t) += m;
}

Mod operator-(const Mod& a, const Mod& b) {
    return Mod(a) -= b;
}

Mod operator-(long t, const Mod& m) {
    return Mod(t) -= m;
}

Mod operator*(const Mod& a, const Mod& b) {
    return Mod(a) *= b;
}

Mod operator*(long t, const Mod& m) {
    return Mod(t) *= m;
}

Mod operator/(const Mod& a, const Mod& b) {
    return Mod(a) /= b;
}

Mod operator/(long t, const Mod& m) {
    return Mod(t) /= m;
}

bool operator==(const Mod& a, const Mod& b) {
    return a.val() == b.val();
}

bool operator==(long t, const Mod& m) {
    return t == m.val();
}

bool operator!=(const Mod& a, const Mod& b) {
    return a.val() != b.val();
}

bool operator!=(long t, const Mod& m) {
    return t != m.val();
}

istream& operator>>(istream& is, Mod& m) {
    long t;
    is >> t;
    m = Mod(t);
    return is;
}

ostream& operator<<(ostream& os, const Mod& m) {
    return os << m.val();
}

int main() {}