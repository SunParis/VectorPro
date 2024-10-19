// vector_pro::sort
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector is now:: [ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 ]
 * myvector after sorting:: [ 12, 32, 32, 39, 46, 55, 61, 72, 84, 97 ]
 */

int main ()
{
  
  // initialize the container with 10 elements
  vector_pro<int> myvector = { 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 };
  std::cout << "myvector is now:: " << myvector << std::endl;

  // sort
  myvector.sort();
  std::cout << "myvector after sorting:: " << myvector << std::endl;

  return 0;
}