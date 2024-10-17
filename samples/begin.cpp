// vector_pro::begin/end
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains: 1 2 3 4 5
 */

int main ()
{
  vector_pro<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (iterator_pro<int> it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}