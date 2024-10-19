// vector_pro::reverse
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector is now:: [ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 ]
 * after reverse:: [ 97, 39, 84, 61, 12, 32, 46, 55, 72, 32 ]
 */

int main ()
{
  
  // push 10 elements into the container
  vector_pro<int> myvector = { 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 };
  std::cout << "myvector is now:: " << myvector << std::endl;

  // reverse
  myvector.reverse();
  std::cout << "after reverse:: " << myvector << std::endl;

  return 0;
}