// vector_pro::empty/not_empty
#include <iostream>
#include "../vector_pro.hpp"

/**
 * Output:
 * total: 55
 */

int main ()
{
  vector_pro<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

  while (!myvector.empty() && myvector.not_empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}