// resizing vector_pro
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains: 1 2 3 4 5 100 100 100
 */

int main ()
{
  vector_pro<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (int i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}