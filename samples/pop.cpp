// vector_pro::pop
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * 300
 * 200
 * 100
 */

int main ()
{
  vector_pro<int> myvector;
  
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  std::cout << myvector.pop() << '\n';
  std::cout << myvector.pop() << '\n';
  std::cout << myvector.pop() << '\n';

  return 0;
}