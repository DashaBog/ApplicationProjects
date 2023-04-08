#include "stringt.h"

int main() {
 /* String s = "aba";
  s.Resize(10, 'a');
  std::cout << (s.Size() == 10);
  std::cout << (s[4] == 'a');
  std::cout << (s[0] == 'a');
  std::cout << (s[9] == 'a');*/

  String s = "abob";
  auto p = s.Data();
  bool are_same = std::is_same_v<decltype(s.Data()), char*>;
  std::cout << are_same;

  return 0;
}