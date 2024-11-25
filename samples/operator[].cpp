// vector_pro::operator[]
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains: 9 8 7 6 5 4 3 2 1 0
 */

int main ()
{
  vector_pro<int> myvector (10, 0);   // 10 zero-initialized elements

  size_type sz = myvector.size();

  // assign some values:
  for (unsigned i=0; i<sz; i++) myvector[i]=i;

  // reverse vector using operator[]:
  for (unsigned i=0; i<sz/2; i++)
  {
    int temp;
    temp = myvector[sz-1-i];
    myvector[sz-1-i]=myvector[i];
    myvector[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sz; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}