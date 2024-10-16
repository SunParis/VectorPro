// vector_pro::operator=
#include <iostream>
#include "../vector_pro.hpp"

/**
 * Output:
 * Size of foo: 0
 * Size of bar: 3
 */

int main ()
{
  vector_pro<int> foo (3,0);
  vector_pro<int> bar (5,0);

  bar = foo;
  foo = vector_pro<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  return 0;
}