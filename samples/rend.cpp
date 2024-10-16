// vector_pro::rbegin/rend
#include <iostream>
#include "../vector_pro.hpp"

/**
 * Output:
 * myvector contains: 5 4 3 2 1
 */

int main ()
{
  vector_pro<int> myvector (5, 0);  // 5 default-constructed ints

  int i=0;

  iterator_pro<int> rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (auto it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}