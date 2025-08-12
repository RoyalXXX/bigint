/*
	bigint
	
	Copyright (c) 2025 Royal_X (MIT License)
 
 	https://github.com/RoyalXXX
  	https://royalxxx.itch.io
   	https://sourceforge.net/u/royal-x
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <stdexcept>

#include "bigint.h"

inline const BigInt ZERO;
inline const BigInt ONE{"1"};
inline const BigInt TWO{"2"};
inline const BigFrac F_ZERO;
inline const BigFrac F_ONE{"1", "1"};

static inline int IntegerQ(const std::string& s)
{
    if (s.empty())
        return 0;
    if (s.length() > 1)
    {
        if (s[0] == '0')
            return 0;
        else if (s[0] == '-')
        {
            if (s[1] == '0')
                return 0;
            if (!std::all_of(s.cbegin() + 1, s.cend(), isdigit))
                    return 0;
            return -1; // Negative integer
        }
    }
    if (!std::all_of(s.cbegin(), s.cend(), isdigit))
            return 0;
    return 1; // Non-negative integer
}

BigInt::BigInt(const char* s) : BigInt(std::string(s)) {}
BigInt::BigInt(const std::string& s)
    : value(s)
{
    auto s_q = IntegerQ(value);
    if (s_q == 0)
    {
        throw std::invalid_argument("ERROR: Not a number");
    }
    if (s_q == -1)
    {
        value.erase(0, 1);
        sign = true;
    }
}
BigInt::BigInt(std::string&& s)
    : value(std::move(s))
{
    auto s_q = IntegerQ(value);
    if (s_q == 0)
    {
        throw std::invalid_argument("ERROR: Not a number");
    }
    if (s_q == -1)
    {
        value.erase(0, 1);
        sign = true;
    }
}

BigInt& BigInt::operator=(const char* s)
{
    value = std::string(s);
    auto s_q = IntegerQ(value);
    if (s_q == 0)
    {
        throw std::invalid_argument("ERROR: Not a number");
    }
    if (s_q == -1)
    {
        value.erase(0, 1);
        sign = true;
    }
    else
        sign = false;
    return *this;
}
BigInt& BigInt::operator+=(const BigInt& x)
{
    *this = *this + x;
    return *this;
}
BigInt& BigInt::operator-=(const BigInt& x)
{
    *this = *this - x;
    return *this;
}
BigInt& BigInt::operator*=(const BigInt& x)
{
    *this = *this * x;
    return *this;
}
BigInt& BigInt::operator/=(const BigInt& x)
{
    *this = *this / x;
    return *this;
}
BigInt& BigInt::operator%=(const BigInt& x)
{
    *this = *this % x;
    return *this;
}
BigInt& BigInt::operator^=(const int p)
{
    *this = *this ^ p;
    return *this;
}

const std::string& BigInt::get_value() const {return value;}
bool BigInt::get_sign() const {return sign;}

std::ostream& operator<<(std::ostream& out, const BigInt& x)
{
    if (x.sign)
        return out << '-' << x.value;
    return out << x.value;
}

BigInt operator+(const BigInt& x, const BigInt& y)
{

    if (!x.sign && y.sign)
        return x - Abs(y);
    if (x.sign && !y.sign)
        return y - Abs(x);
    std::string a, b;
    a.assign(x.value.crbegin(), x.value.crend());
    b.assign(y.value.crbegin(), y.value.crend());
    if (b.length() > a.length())
        std::swap(a, b);
    int c{}, d;
    for (std::size_t i{}; i < a.length(); ++i)
    {
        if (c == 0 && i >= b.length())
            break;
        if (i < b.length())
            d = a[i] - '0' + b[i] - '0' + c;
        else
            d = a[i] - '0' + c;
        a[i] = d % 10 + '0';
        c = d / 10;
    }
    if (c != 0)
        a.push_back('1');
    std::reverse(a.begin(), a.end());
    BigInt z;
    z.value = a;
    if (x.sign && y.sign)
        z.sign = true;
    return z;
}
BigInt operator-(const BigInt& x, const BigInt& y)
{
    if (!x.sign && y.sign)
        return x + Abs(y);
    if (x.sign && !y.sign)
    {
        BigInt z = Abs(x) + y;
        z.sign = true;
        return z;
    }
    if (x.sign && y.sign)
        return Abs(y) - Abs(x);
    if (x < y)
    {
        BigInt z = y - x;
        z.sign = true;
        return z;
    }
    std::string a(x.value.crbegin(), x.value.crend());
    std::string b(y.value.crbegin(), y.value.crend());
    int c{}, d;
    for (std::size_t i{}; i < a.length(); ++i)
    {
        if (c == 0 && i >= b.length())
            break;
        if (i < b.length())
            d = a[i] - b[i] - c;
        else
            d = a[i] - '0' - c;
        if (d < 0)
        {
            a[i] = 10 + d + '0';
            c = 1;
        }
        else
        {
            a[i] = d + '0';
            c = 0;
        }
    }
    while (a.back() == '0' && a.length() > 1)
        a.pop_back();
    std::reverse(a.begin(), a.end());
    BigInt z;
    z.value = a;
    return z;
}
BigInt operator-(const BigInt& x)
{
    BigInt y{x};
    y.sign = !y.sign;
    return y;
}
BigInt operator*(const BigInt& x, const BigInt& y)
{
    if (x.sign && y.sign)
        return Abs(x) * Abs(y);
    if (x.value == "0" || y.value == "0")
        return ZERO;
    if (x.sign)
    {
        BigInt z = Abs(x) * y;
        z.sign = true;
        return z;
    }
    if (y.sign)
    {
        BigInt z = x * Abs(y);
        z.sign = true;
        return z;
    }
    if (x.value == "1")
        return y;
    if (y.value == "1")
        return x;
    BigInt z;
    std::string a(x.value.crbegin(), x.value.crend()), b(y.value.crbegin(), y.value.crend()), temp;
    temp.reserve(a.size() + 1);
    for (std::size_t i{}; i < b.size(); ++i)
    {
        temp.clear();
        for (std::size_t k{}; k < i; ++k)
            temp.push_back('0');
        int c{};
        for (const auto& j : a)
        {
            int d = (b[i] - '0') * (j - '0') + c;
            temp.push_back(d % 10 + '0');
            c = d / 10;
        }
        if (c > 0)
            temp.push_back(c + '0');
        std::reverse(temp.begin(), temp.end());
        BigInt t;
        t.value = temp;
        z += t;
    }
    return z;
}
BigInt operator/(const BigInt& x, const BigInt& y)
{
    if (y.value == "0")
    {
        throw std::runtime_error("Division by zero");
    }
    if (x.value == "0")
        return ZERO;
    if (x.sign && y.sign)
        return Abs(x) / Abs(y);
    if (x.sign)
    {
        BigInt z = Abs(x) / y;
        z.sign = true;
        return z;
    }
    if (y.sign)
    {
        BigInt z = x / Abs(y);
        z.sign = true;
        return z;
    }
    if (x.value == y.value)
        return ONE;
    if (y.value == "1")
        return x;
    if (x < y)
        return ZERO;
    BigInt rem;
    rem.value = std::string(x.value.cbegin(), x.value.cbegin() + y.value.length());
    if (rem < y)
        rem.value.push_back(x.value[y.value.length()]);
    auto i = rem.value.length();
    BigInt z;
    while (rem >= y)
    {
        rem -= y;
        z += ONE;
    }
    for (; i < x.value.length(); ++i)
    {
        z.value.push_back('0');
        if (rem.value == "0")
            rem.value.clear();
        rem.value.push_back(x.value[i]);
        while (rem >= y)
        {
            rem -= y;
            BigInt w;
            w.value = std::string(1, z.value.back());
            z.value.back() = (w + ONE).value[0];
        }
    }
    return z;
}
BigInt operator%(const BigInt& x, const BigInt& y)
{
    if (y.value == "0")
    {
        throw std::runtime_error("Division by zero");
    }
    if (x.sign && y.sign)
        return Abs(x) % Abs(y);
    if (x.value == "0")
        return ZERO;
    if (x.sign)
    {
        BigInt z = Abs(x) % y;
        z.sign = true;
        return z;
    }
    if (y.sign)
        return x % Abs(y);
    if (x.value == y.value || y.value == "1")
        return ZERO;
    if (x < y)
        return x;
    BigInt rem;
    rem.value = std::string(x.value.cbegin(), x.value.cbegin() + y.value.length());
    if (rem < y)
        rem.value.push_back(x.value[y.value.length()]);
    auto i = rem.value.length();
    while (rem >= y)
        rem -= y;
    for (; i < x.value.length(); ++i)
    {
        if (rem.value == "0")
            rem.value.clear();
        rem.value.push_back(x.value[i]);
        while (rem >= y)
            rem -= y;
    }
    return rem;
}
BigInt operator^(const BigInt& x, const int y)
{
    if (y < 0)
    {
        throw std::domain_error("Power is a negative integer");
    }
    if (x.value == "0" && y == 0)
    {
        throw std::domain_error("Indeterminate expression 0^0 encountered");
    }
    if (x.value == "0")
        return x;
    if (y == 0)
        return ONE;
    if (x.sign)
    {
        if (y % 2 == 0)
            return Abs(x) ^ y;
        else
        {
            BigInt z = Abs(x) ^ y;
            z.sign = true;
            return z;
        }
    }
    if (y == 1)
        return x;
    BigInt z(x);
    for (int i{1}; i < y; ++i)
        z *= x;
    return z;
}

bool operator>=(const BigInt& x, const BigInt& y)
{
    if (!x.sign && y.sign)
        return true;
    if (x.sign && !y.sign)
        return false;
    // x and y are negative
    if (x.sign && y.sign)
    {
        if (x.value.length() < y.value.length())
            return true;
        if (x.value.length() > y.value.length())
            return false;
        if (x.value.compare(y.value) <= 0)
            return true;
        return false;
    }
    // x and y are positive
    if (x.value.length() > y.value.length())
        return true;
    if (x.value.length() < y.value.length())
        return false;
    if (x.value.compare(y.value) >= 0)
        return true;
    return false;
}
bool operator<=(const BigInt& x, const BigInt& y)
{
    if (!x.sign && y.sign)
        return false;
    if (x.sign && !y.sign)
        return true;
    // x and y are negative
    if (x.sign && y.sign)
    {
        if (x.value.length() > y.value.length())
            return true;
        if (x.value.length() < y.value.length())
            return false;
        if (x.value.compare(y.value) >= 0)
            return true;
        return false;
    }
    // x and y are positive
    if (x.value.length() < y.value.length())
        return true;
    if (x.value.length() > y.value.length())
        return false;
    if (x.value.compare(y.value) <= 0)
        return true;
    return false;
}
bool operator==(const BigInt& x, const BigInt& y)
{
    if (x.sign == y.sign && x.value == y.value)
        return true;
    return false;
}
bool operator!=(const BigInt& x, const BigInt& y)
{
    return !(x == y);
}
bool operator>(const BigInt& x, const BigInt& y)
{
    if (!x.sign && y.sign)
        return true;
    if (x.sign && !y.sign)
        return false;
    // x and y are negative
    if (x.sign && y.sign)
    {
        if (x.value.length() < y.value.length())
            return true;
        if (x.value.length() > y.value.length())
            return false;
        if (x.value.compare(y.value) < 0)
            return true;
        return false;
    }
    // x and y are positive
    if (x.value.length() > y.value.length())
        return true;
    if (x.value.length() < y.value.length())
        return false;
    if (x.value.compare(y.value) > 0)
        return true;
    return false;
}
bool operator<(const BigInt& x, const BigInt& y)
{
    if (!x.sign && y.sign)
        return false;
    if (x.sign && !y.sign)
        return true;
    // x and y are negative
    if (x.sign && y.sign)
    {
        if (x.value.length() > y.value.length())
            return true;
        if (x.value.length() < y.value.length())
            return false;
        if (x.value.compare(y.value) > 0)
            return true;
        return false;
    }
    // x and y are positive
    if (x.value.length() < y.value.length())
        return true;
    if (x.value.length() > y.value.length())
        return false;
    if (x.value.compare(y.value) < 0)
        return true;
    return false;
}

BigInt Abs(const BigInt& x)
{
    BigInt y{x};
    y.sign = false;
    return y;
}
BigInt Factorial(const int n)
{
    if (n < 0)
    {
        throw std::domain_error("Factorial of a negative integer");
    }
    BigInt x{ONE};
    int c{0};
    for (int i{2}; i <= n; ++i)
    {
        for (std::size_t j{}; j < x.value.length(); ++j)
        {
            int p = (x.value[j] - '0') * i + c;
            x.value[j] = p % 10 + '0';
            c = p / 10;
        }
        while (c > 0)
        {
            x.value.push_back(c % 10 + '0');
            c /= 10;
        }
    }
    std::reverse(x.value.begin(), x.value.end());
    return x;
}
BigInt GCD(const BigInt& x, const BigInt& y)
{
    if(x.value == "0" && y.value == "0")
        return ZERO;
    if (x.sign && !y.sign)
        return GCD(Abs(x), y);
    if (!x.sign && y.sign)
        return GCD(x, Abs(y));
    if (x.sign && y.sign)
        return GCD(Abs(x), Abs(y));
    if (y.value == "0")
        return x;
    else
        return GCD(y, x % y);
}
BigInt LCM(const BigInt& x, const BigInt& y)
{
    if (x.value == "0" || y.value == "0")
        return ZERO;
    if (x.sign && !y.sign)
        return GCD(Abs(x), y);
    if (!x.sign && y.sign)
        return GCD(x, Abs(y));
    if (x.sign && y.sign)
        return GCD(Abs(x), Abs(y));
    return Abs(y) * (Abs(x) / GCD(x, y));
}
BigInt ISqrt(const BigInt& x)
{
    if (x.sign)
    {
        throw std::domain_error("Integer square root of a negative integer");
    }
    if (x.value == "0" || x.value == "1")
        return x;
    auto x0 = x / TWO;
    auto x1 = (x0 + x / x0) / TWO;
    while (!(x1 >= x0))
    {
        x0 = x1;
        x1 = (x0 + x / x0) / TWO;
    }
    return x0;
}
BigInt Fibonacci(const int n)
{
    if (n < 0)
    {
        throw std::domain_error("Fibonacci of a negative integer");
    }
    if (n == 0)
        return ZERO;
    BigInt a, b{ONE}, c;
    for (int i = 2; i <= n; ++i)
    {
        c = a + b;
        a.value = b.value;
        b.value = c.value;
    }
    return b;
}
BigInt Binomial(const int n, const int k)
{
    if (n < 0 || k < 0 || k > n)
        return ZERO;
    if (n == k || k == 0)
        return ONE;
    return Factorial(n) / Factorial(k) / Factorial(n - k);
}
bool EvenQ(const BigInt& x)
{
    return (x.value.back() - '0') % 2 == 0;
}
bool OddQ(const BigInt& x)
{
    return !EvenQ(x);
}
std::size_t IntegerLength(const BigInt& x)
{
    return x.value.length();
}
std::string Approx(const BigInt& x, const std::size_t n)
{
    std::string s;
    if (x.sign)
        s.push_back('-');
    auto d = x.value.substr(0, std::clamp(n, 1ull, x.value.length()));
    if (d != "0")
        d.erase(d.find_last_not_of('0') + 1);
    if (d.length() > 1)
        d.insert(1, 1, '.');
    s += d + " x 10 ^ " + std::to_string(x.value.length() - 1ull);
    return s;
}

static inline void Reduce(BigInt& x, BigInt& y)
{
    auto g = GCD(x, y);
    if (g.get_value() != "1")
    {
        x /= g;
        y /= g;
    }
    if (x.get_sign() && y.get_sign())
    {
        x = Abs(x);
        y = Abs(y);
    }
    else if (y.get_sign())
    {
        x = -x;
        y = Abs(y);
    }
}

BigFrac::BigFrac(const BigInt& x, const BigInt& y)
    : num(x)
    , denom(y)
{
    if (denom.get_value() == "0")
    {
        throw std::runtime_error("Division by zero");
    }
    Reduce(num, denom);
}

const BigInt& BigFrac::get_numerator() const {return num;}
const BigInt& BigFrac::get_denominator() const {return denom;}

std::ostream& operator<<(std::ostream& out, const BigFrac& x)
{
    if (x.num.get_sign() && x.denom.get_sign())
        return out << '-' << x.num.get_value() << " / -" << x.denom.get_value();
    if (!x.num.get_sign() && x.denom.get_sign())
        return out << x.num.get_value() << " / -" << x.denom.get_value();
    if (x.num.get_sign() && !x.denom.get_sign())
        return out << '-' << x.num.get_value() << " / " << x.denom.get_value();
    return out << x.num.get_value() << " / " << x.denom.get_value();
}

BigFrac& BigFrac::operator+=(const BigFrac& x)
{
    *this = *this + x;
    return *this;
}
BigFrac& BigFrac::operator-=(const BigFrac& x)
{
    *this = *this - x;
    return *this;
}
BigFrac& BigFrac::operator*=(const BigFrac& x)
{
    *this = *this * x;
    return *this;
}
BigFrac& BigFrac::operator/=(const BigFrac& x)
{
    *this = *this / x;
    return *this;
}
BigFrac& BigFrac::operator^=(const int p)
{
    *this = *this ^ p;
    return *this;
}

BigFrac operator+(const BigFrac& x, const BigFrac& y)
{
    BigFrac z;
    z.denom = x.denom * y.denom;
    z.num = x.num * (z.denom / x.denom) + y.num * (z.denom / y.denom);
    Reduce(z.num, z.denom);
    return z;
}
BigFrac operator-(const BigFrac& x, const BigFrac& y)
{
    BigFrac z;
    z.denom = x.denom * y.denom;
    z.num = x.num * (z.denom / x.denom) - y.num * (z.denom / y.denom);
    Reduce(z.num, z.denom);
    return z;
}
BigFrac operator-(const BigFrac& x)
{
    BigFrac z{x};
    z.num = -z.num;
    return z;
}
BigFrac operator*(const BigFrac& x, const BigFrac& y)
{
    BigFrac z;
    z.num = x.num * y.num;
    z.denom = x.denom * y.denom;
    Reduce(z.num, z.denom);
    return z;
}
BigFrac operator/(const BigFrac& x, const BigFrac& y)
{
    if (y.num.get_value() == "0")
    {
        throw std::runtime_error("Division by zero");
    }
    BigFrac z;
    z.num = x.num * y.denom;
    z.denom = x.denom * y.num;
    Reduce(z.num, z.denom);
    return z;
}
BigFrac operator^(const BigFrac& x, const int y)
{
    if (x.num.get_value() == "0")
    {
        if (y == 0)
        {
            throw std::domain_error("Indeterminate expression 0^0 encountered");
        }
        if (y < 0)
        {
            throw std::runtime_error("Division by zero");
        }
    }
    if (y == 0)
        return F_ONE;
    BigFrac z{x};
    for (int i{1}; i < std::abs(y); ++i)
    {
        z.num *= x.num;
        z.denom *= x.denom;
    }
    if (y < 0)
        std::swap(z.num, z.denom);
    return z;
}

bool operator>=(const BigFrac& x, const BigFrac& y)
{
    return x == y || x > y;
}
bool operator<=(const BigFrac& x, const BigFrac& y)
{
    return x == y || x < y;
}
bool operator>(const BigFrac& x, const BigFrac& y)
{
    if (!x.num.get_sign() && y.num.get_sign())
        return true;
    if (x.num.get_sign() && !y.num.get_sign())
        return false;
    // x and y are negative
    if (x.num.get_sign() && y.num.get_sign())
    {
        if (x.denom.get_value() == y.denom.get_value())
        {
            if (x.num.get_value() < y.num.get_value())
                return true;
            if (x.num.get_value() > y.num.get_value())
                return false;
        }
        if (x.num.get_value() == y.num.get_value())
        {
            if (x.denom.get_value() > y.denom.get_value())
                return true;
            if (x.denom.get_value() < y.denom.get_value())
                return false;
        }
        if (x.num.get_value() * y.denom.get_value() < x.denom.get_value() * y.num.get_value())
            return true;
        return false;
    }
    // x and y are positive
    if (x.denom.get_value() == y.denom.get_value())
    {
        if (x.num.get_value() > y.num.get_value())
            return true;
        if (x.num.get_value() < y.num.get_value())
            return false;
    }
    if (x.num.get_value() == y.num.get_value())
    {
        if (x.denom.get_value() < y.denom.get_value())
            return true;
        if (x.denom.get_value() > y.denom.get_value())
            return false;
    }
    if (x.num.get_value() * y.denom.get_value() > x.denom.get_value() * y.num.get_value())
        return true;
    return false;
}
bool operator<(const BigFrac& x, const BigFrac& y)
{
    if (!x.num.get_sign() && y.num.get_sign())
        return false;
    if (x.num.get_sign() && !y.num.get_sign())
        return true;
    // x and y are negative
    if (x.num.get_sign() && y.num.get_sign())
    {
        if (x.denom.get_value() == y.denom.get_value())
        {
            if (x.num.get_value() > y.num.get_value())
                return true;
            if (x.num.get_value() < y.num.get_value())
                return false;
        }
        if (x.num.get_value() == y.num.get_value())
        {
            if (x.denom.get_value() < y.denom.get_value())
                return true;
            if (x.denom.get_value() > y.denom.get_value())
                return false;
        }
        if (x.num.get_value() * y.denom.get_value() > x.denom.get_value() * y.num.get_value())
            return true;
        return false;
    }
    // x and y are positive
    if (x.denom.get_value() == y.denom.get_value())
    {
        if (x.num.get_value() < y.num.get_value())
            return true;
        if (x.num.get_value() > y.num.get_value())
            return false;
    }
    if (x.num.get_value() == y.num.get_value())
    {
        if (x.denom.get_value() > y.denom.get_value())
            return true;
        if (x.denom.get_value() < y.denom.get_value())
            return false;
    }
    if (x.num.get_value() * y.denom.get_value() < x.denom.get_value() * y.num.get_value())
        return true;
    return false;
}
bool operator==(const BigFrac& x, const BigFrac& y)
{
    if (x.num.get_sign() != y.num.get_sign())
        return false;
    if (x.num.get_value() != y.num.get_value())
        return false;
    if (x.denom.get_value() != y.denom.get_value())
        return false;
    return true;
}
bool operator!=(const BigFrac& x, const BigFrac& y)
{
    return !(x == y);
}

BigFrac Abs(const BigFrac& x)
{
    BigFrac y;
    y.num = x.num;
    y.denom = x.denom;
    return y;
}
BigFrac Harmonic(const int n)
{
    if (n < 0)
    {
        throw std::domain_error("Complex infinity");
    }
    if (n == 0)
        return F_ZERO;
    BigFrac x{F_ONE};
    BigFrac t{F_ONE};
    for (int i{2}; i <= n; ++i)
    {
        t.denom = std::to_string(i);
        x += t;
    }
    return x;
}
std::string Approx(const BigFrac& x)
{
    std::string s;
    if (x.num.get_sign())
        s.push_back('-');
    auto exp_num = x.num.get_value().length() - 1;
    auto exp_denom = x.denom.get_value().length() - 1;
    long long exponent = exp_num - exp_denom;
    std::string s_num = x.num.get_value().substr(0, std::min(x.num.get_value().length(), 17ull));
    std::string s_denom = x.denom.get_value().substr(0, std::min(x.denom.get_value().length(), 17ull));
    s_num.insert(1, 1, '.');
    s_denom.insert(1, 1, '.');
    double m_num = std::stod(s_num);
    double m_denom = std::stod(s_denom);
    double mantissa = m_num / m_denom;
    if (mantissa < 1.)
    {
        mantissa *= 10.;
        --exponent;
    }
    std::stringstream ss;
    ss.precision(16);
    ss << mantissa;
    s += ss.str() + " x 10 ^ " + std::to_string(exponent);
    return s;
}

