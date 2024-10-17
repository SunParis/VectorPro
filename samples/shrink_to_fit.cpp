// vector_pro::shrink_to_fit
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * 1. capacity of myvector: 100
 * 2. capacity of myvector: 10
 * 3. capacity of myvector: 10
 */

int main ()
{
  vector_pro<int> myvector (100, 0);
  std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';

  myvector.resize(10);
  std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';

  myvector.shrink_to_fit();
  std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';

  return 0;
}