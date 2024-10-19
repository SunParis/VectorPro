// vector_pro::merge
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector is now:: [ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 ]
 * myvector2 is now:: [ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 ]
 * myvector after merging:: [ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97, 100, 100, 100, 100, 100 ]
 * myvector2 after merging:: [ 100, 100, 100, 100, 100 ]
 */

int main ()
{
  
  // initialize the containers
  vector_pro<int> myvector = { 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 };
  vector_pro<int> myvector2(5, 100);
  std::cout << "myvector is now:: " << myvector << std::endl;
  std::cout << "myvector2 is now:: " << myvector << std::endl;

  // merge
  myvector.merge(myvector2);
  std::cout << "myvector after merging:: " << myvector << std::endl;
  std::cout << "myvector2 after merging:: " << myvector2 << std::endl;

  return 0;
}