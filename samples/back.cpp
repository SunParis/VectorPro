// vector_pro::back
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains: 10 9 8 7 6 5 4 3 2 1 0
 */

int main ()
{
  vector_pro<int> myvector;

  myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}