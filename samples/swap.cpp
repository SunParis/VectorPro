// vector_pro::swap
#include <iostream>
#include "../vector_pro.hpp"

/**
 * Output:
 * foo contains: 200 100 200 200 200
 * bar contains: 100 100 200
 */

int main ()
{
  vector_pro<int> foo (3,100);   // three ints with a value of 100
  vector_pro<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);
  foo.swap(bar.begin() + 2, foo.begin() + 1);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo.size(); i++)
    std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar.size(); i++)
    std::cout << ' ' << bar[i];
  std::cout << '\n';

  return 0;
}