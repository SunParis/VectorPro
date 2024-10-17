// vector_pro::pop_back
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * The elements of myvector add up to 600
 */

int main ()
{
  vector_pro<int> myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  return 0;
}