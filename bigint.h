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

#pragma once

#include <iostream>
#include <string>

class BigInt
{
private:
    std::string value = "0";
    bool sign = false;
public:
    BigInt()=default;
    BigInt(const std::string&);
    BigInt(std::string&&);
    BigInt(const char*);

    BigInt& operator=(const char*);
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator^=(const int);

    const std::string& get_value() const;
    bool get_sign() const;
    
    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator%(const BigInt&, const BigInt&);
    friend BigInt operator^(const BigInt&, const int);

    friend bool operator>=(const BigInt&, const BigInt&);
    friend bool operator<=(const BigInt&, const BigInt&);
    friend bool operator==(const BigInt&, const BigInt&);
    friend bool operator!=(const BigInt&, const BigInt&);
    friend bool operator>(const BigInt&, const BigInt&);
    friend bool operator<(const BigInt&, const BigInt&);
    
    friend BigInt Abs(const BigInt&);
    friend BigInt Factorial(const int);
    friend BigInt GCD(const BigInt&, const BigInt&);
    friend BigInt LCM(const BigInt&, const BigInt&);
    friend BigInt ISqrt(const BigInt&);
    friend BigInt Fibonacci(const int);
    friend BigInt Binomial(const int, const int);
    friend bool EvenQ(const BigInt&);
    friend bool OddQ(const BigInt&);
    friend std::size_t IntegerLength(const BigInt&);
    friend std::string Approx(const BigInt&, const std::size_t);
};

inline BigInt Add(const BigInt& x, const BigInt& y){return x + y;}
inline BigInt Subtract(const BigInt& x, const BigInt& y){return x - y;}
inline BigInt Minus(const BigInt& x){return -x;}
inline BigInt Multiply(const BigInt& x, const BigInt& y){return x * y;}
inline BigInt Divide(const BigInt& x, const BigInt& y){return x / y;}
inline BigInt Remainder(const BigInt& x, const BigInt& y){return x % y;}
inline BigInt Pow(const BigInt& x, const int y){return x ^ y;}

inline bool EqualQ(const BigInt& x, const BigInt& y){return x == y;}
inline bool NotEqualQ(const BigInt& x, const BigInt& y){return x != y;}
inline bool GreaterQ(const BigInt& x, const BigInt& y){return x > y;}
inline bool LessQ(const BigInt& x, const BigInt& y){return x < y;}
inline bool GreaterEqualQ(const BigInt& x, const BigInt& y){return x >= y;}
inline bool LessEqualQ(const BigInt& x, const BigInt& y){return x <= y;}

BigInt Abs(const BigInt&);
BigInt Factorial(const int);
BigInt GCD(const BigInt&, const BigInt&);
BigInt LCM(const BigInt&, const BigInt&);
BigInt ISqrt(const BigInt&);
BigInt Fibonacci(const int);
BigInt Binomial(const int, const int);
bool EvenQ(const BigInt&);
bool OddQ(const BigInt&);
std::size_t IntegerLength(const BigInt&);
std::string Approx(const BigInt&, const std::size_t = 10ull);

class BigFrac
{
private:
    BigInt num;
    BigInt denom{"1"};
public:
    BigFrac()=default;
    BigFrac(const BigInt&, const BigInt&);

    const BigInt& get_numerator() const;
    const BigInt& get_denominator() const;

    friend std::ostream& operator<<(std::ostream&, const BigFrac&);

    BigFrac& operator+=(const BigFrac&);
    BigFrac& operator-=(const BigFrac&);
    BigFrac& operator*=(const BigFrac&);
    BigFrac& operator/=(const BigFrac&);
    BigFrac& operator^=(const int);

    friend BigFrac operator+(const BigFrac&, const BigFrac&);
    friend BigFrac operator-(const BigFrac&, const BigFrac&);
    friend BigFrac operator-(const BigFrac&);
    friend BigFrac operator*(const BigFrac&, const BigFrac&);
    friend BigFrac operator/(const BigFrac&, const BigFrac&);
    friend BigFrac operator^(const BigFrac&, const int);

    friend bool operator>=(const BigFrac&, const BigFrac&);
    friend bool operator<=(const BigFrac&, const BigFrac&);
    friend bool operator==(const BigFrac&, const BigFrac&);
    friend bool operator!=(const BigFrac&, const BigFrac&);
    friend bool operator>(const BigFrac&, const BigFrac&);
    friend bool operator<(const BigFrac&, const BigFrac&);

    friend BigFrac Abs(const BigFrac&);
    friend BigFrac Harmonic(const int);
    friend std::string Approx(const BigFrac&);
};

inline BigFrac Add(const BigFrac& x, const BigFrac& y){return x + y;}
inline BigFrac Subtract(const BigFrac& x, const BigFrac& y){return x - y;}
inline BigFrac Minus(const BigFrac& x){return -x;}
inline BigFrac Multiply(const BigFrac& x, const BigFrac& y){return x * y;}
inline BigFrac Divide(const BigFrac& x, const BigFrac& y){return x / y;}
inline BigFrac Pow(const BigFrac& x, const int y){return x ^ y;}

inline bool EqualQ(const BigFrac& x, const BigFrac& y){return x == y;}
inline bool NotEqualQ(const BigFrac& x, const BigFrac& y){return x != y;}
inline bool GreaterQ(const BigFrac& x, const BigFrac& y){return x > y;}
inline bool LessQ(const BigFrac& x, const BigFrac& y){return x < y;}
inline bool GreaterEqualQ(const BigFrac& x, const BigFrac& y){return x >= y;}
inline bool LessEqualQ(const BigFrac& x, const BigFrac& y){return x <= y;}

BigFrac Abs(const BigFrac&);
BigFrac Harmonic(const int);

std::string Approx(const BigFrac&);
