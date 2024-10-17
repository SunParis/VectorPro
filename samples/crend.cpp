// vector_pro::crbegin/crend
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector backwards: 5 4 3 2 1
 */

int main ()
{
  vector_pro<int> myvector = {1,2,3,4,5};

  std::cout << "myvector backwards:";
  for (auto rit = myvector.crbegin(); rit != myvector.crend(); ++rit)
    std::cout << ' ' << *rit;
  std::cout << '\n';

  return 0;
}