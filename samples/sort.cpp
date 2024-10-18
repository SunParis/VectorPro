// vector_pro::sort
#include <iostream>
#include "../vector_pro.h"
#include <cstdlib>
#include <ctime>

/**
 * Output:
 * myvector is now:: [ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 ]
 * myvector after sorting:: [ 12, 32, 32, 39, 46, 55, 61, 72, 84, 97 ]
 */

int main ()
{
  vector_pro<int> myvector;
  
  // push 30 random elements into the container
  std::srand(std::time(0));
  for (int i = 0; i < 10; i++)  myvector.push_back(std::rand() % 100);
  std::cout << "myvector is now:: " << myvector << std::endl;

  // sort
  myvector.sort();

  std::cout << "myvector after sorting:: " << myvector << std::endl;

  return 0;
}