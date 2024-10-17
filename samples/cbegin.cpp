// vector_pro::cbegin/cend
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains: 10 20 30 40 50
 */

int main ()
{
  vector_pro<int> myvector = {10,20,30,40,50};

  std::cout << "myvector contains:";

  for (auto it = myvector.cbegin(); it != myvector.cend(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}