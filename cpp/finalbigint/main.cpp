#include "big_integer.h"
#include<limits>

int main() {
 /* BigInt zero(0);
  std::cout << (zero == 0);
  std::cout << (-zero == 0);
  std::cout << (-(-(-zero)) == 0);*/
  std::istringstream iss("1234567890123456789012345 -1234567890123456789012");
  std::ostringstream oss;

  BigInt a;
  BigInt b;
  /*iss >> a;
  oss << a << "\n";
  iss >> b;
  oss << b;*/
 /* std::cin >> a >> b;
  std::cout << a << ' ' << b << '\n';*/
  iss >> a >> b;
  oss << a << ' ' << b << '\n';

  // BigInt s(std::numeric_limits<int64_t>::min());
//  std::cin >> s;
 // BigInt ss(std::numeric_limits<int64_t>::max());
  /*std::cout << (s < ss);
  std::cout << (s <= ss);
  std::cout << (s > ss);
  std::cout << (s >= ss);
  std::cout << (s == ss);
  std::cout << (s != ss) << "\n";
  std::cout << (s + ss) << "\n";*/
//  std::cout << (s - ss) << "\n";
/*  std::cout << (s * ss) << "\n";
  std::cout << (s / ss) << "\n";
  std::cout << (s % ss) << "\n";
  std::cout << (++s) << "\n";
  std::cout << (--s) << "\n";
  std::cout << (s++) << "\n";
  std::cout << (s--) << "\n";
  std::cout << s << "\n";
  std::cout << (-s) << "\n";*/
  return 0;
}
