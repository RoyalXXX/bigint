# bigint
## Simple C++ Library for Large Integers and Fractions

**bigint** is a lightweight C++ library for working with large integers and fractions. It is designed with simplicity in mind, requiring only a single header and a single implementation file.

## Features
- Supports arbitrarily large integers
- Fractional (rational) number support
- Minimalistic and easy to integrate
- No external dependencies
## Usage
Simply include the provided files and start using big integers and big fractions effortlessly in your C++ projects.

# Documentation
## Declaring and Intializing Variables

``` c++
#include <string> // std::string
#include "bigint.h"
 
int main() 
{
    BigInt a("1"); 
    BigInt b{"2"}; // uniform initialization
    BigInt c = "-3"; // conversion constructor, const char* to BigInt
    BigInt d = {"4"};
    std::string s{"5"};
    BigInt e = s; // conversion constructor, std::string to BigInt
    BigInt f(s);
    BigInt g; // 0
    const char* h = "6";
    BigInt i = h; // conversion constructor, const char* to BigInt
    BigInt j(h);
    BigInt k(a); // copy constructor

    BigFrac l(a, b); // 1/2
    BigFrac m{c, d}; // -3/4
    BigFrac n("1", "3"); 
    BigFrac o = {s, "3"}; // 5/3
    BigFrac p; // 0/1
    BigFrac q = {"5", "15"}; // 1/3 auto simplifying
}
```
## Printing BigInt and BigFrac 
``` c++
#include <iostream>
#include "bigint.h"
 
int main() 
{
    BigInt a("42");
    std::cout << a << std::endl;
    BigFrac c("-1", "2");
    std::cout << c << std::endl;
    std::cout << BigInt("100") << std::endl;
    std::cout << BigFrac("2", "7") << std::endl;
}
```
## Getting the values of member variables
```c++
const std::string& get_value() const
```
```c++
bool get_sign() const
```
```c++
const BigInt& get_numerator() const
```
```c++
const BigInt& get_denominator() const
```
### Example
``` c++
#include <iostream>
#include <string>
#include "bigint.h"
 
int main() 
{
    BigInt a("42");
    std::string value = a.get_value(); // value = "42"
    bool sign = a.get_sign(); // sign = false

    BigFrac b("3", "7");
    BigInt num = b.get_numerator(); // num = "3"
    BigInt den = b.get_denominator(); // den = "7"
}
```
## BigInt Functions
### Basic operations
#### Add +
```c++
BigInt Add(const BigInt& x, const BigInt& y)
```
#### Subtract -
```c++
BigInt Subtract(const BigInt&, const BigInt&)
```
#### Minus -
```c++
BigInt Minus(const BigInt&)
```
#### Multiply *
```c++
BigInt Multiply(const BigInt&, const BigInt&)
```
#### Divide /
```c++
BigInt Divide(const BigInt&, const BigInt&)
```
#### Remainder %
```c++
BigInt Remainder(const BigInt&, const BigInt&)
```
#### Pow ^
```c++
BigInt Pow(const BigInt&, const int)
```
### Advanced operations
#### Abs
```c++
BigInt Abs(const BigInt&)
```
#### Factorial
```c++
BigInt Factorial(const int)
```
#### GCD
```c++
BigInt GCD(const BigInt&, const BigInt&)
```
#### LCM
```c++
BigInt LCM(const BigInt&, const BigInt&)
```
#### ISqrt
```c++
BigInt ISqrt(const BigInt&)
```
#### Fibonacci
```c++
BigInt Fibonacci(const int)
```
#### Binomial
```c++
BigInt Binomial(const int, const int)
```
#### EvenQ
```c++
bool EvenQ(const BigInt&)
```
#### OddQ
```c++
bool OddQ(const BigInt&)
```
#### IntegerLength
```c++
std::size_t IntegerLength(const BigInt&)
```
#### Approx
```c++
std::string Approx(const BigInt&, const std::size_t = 10ull)
```
### Comparison of numbers
#### EqualQ ==
```c++
bool EqualQ(const BigInt&, const BigInt&)
```
#### NotEqualQ !=
```c++
bool NotEqualQ(const BigInt&, const BigInt&)
```
#### GreaterQ >
```c++
bool GreaterQ(const BigInt&, const BigInt&)
```
#### LessQ <
```c++
bool LessQ(const BigInt&, const BigInt&)
```
#### GreaterEqualQ >=
```c++
bool GreaterEqualQ(const BigInt&, const BigInt&)
```
#### LessEqualQ <=
```c++
bool LessEqualQ(const BigInt&, const BigInt&)
```
## BigFrac Functions
### Basic operations
#### Add +
```c++
BigFrac Add(const BigFrac&, const BigFrac&)
```
#### Subtract -
```c++
BigFrac Subtract(const BigFrac&, const BigFrac&)
```
#### Minus -
```c++
BigFrac Minus(const BigFrac&)
```
#### Multiply *
```c++
BigFrac Multiply(const BigFrac&, const BigFrac&)
```
#### Divide /
```c++
BigFrac Divide(const BigFrac&, const BigFrac&)
```
#### Pow ^
```c++
BigFrac Pow(const BigFrac&, const int)
```
### Advanced operations
#### Abs
```c++
BigFrac Abs(const BigFrac&)
```
#### Harmonic
```c++
BigFrac Harmonic(const int)
```
#### Approx
```c++
std::string Approx(const BigFrac&)
```
### Comparison of fractions
#### EqualQ ==
```c++
bool EqualQ(const BigFrac&, const BigFrac&)
```
#### NotEqualQ
```c++
bool NotEqualQ(const BigFrac&, const BigFrac&)
```
#### GreaterQ
```c++
bool GreaterQ(const BigFrac&, const BigFrac&)
```
#### LessQ
```c++
bool LessQ(const BigFrac&, const BigFrac&)
```
#### GreaterEqualQ
```c++
bool GreaterEqualQ(const BigFrac&, const BigFrac&)
```
#### LessEqualQ
```c++
bool LessEqualQ(const BigFrac&, const BigFrac&)
```
