// vector_pro::find
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * (1) the nearest 9 is at:: 8
 * (2) the nearest 9 is at:: 11
 */

int main ()
{
  vector_pro<int> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);
  for (int i=10; i>=0; i--) myvector.push_back(i);

  // find the element 9 from the begin of container
  auto idx = myvector.find (9, myvector.begin(), myvector.end());
  std::cout << "(1) the nearest 9 is at:: " << idx.get_idx() << "\n";

  // find the element 9 reversely from the end of container
  auto idx2 = myvector.find (9, myvector.rbegin(), myvector.rend());
  std::cout << "(2) the nearest 9 is at:: " << idx2.get_idx() << "\n";

  return 0;
}