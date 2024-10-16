// vector_pro::at
#include <iostream>
#include "../vector_pro.hpp"

/**
 * Output:
 * myvector contains: 0 1 2 3 4 5 6 7 8 9
 */

int main ()
{
  vector_pro<int> myvector(10, 0);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  return 0;
}