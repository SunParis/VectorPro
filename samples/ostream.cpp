// vector_pro::operator<<
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains:[ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 ]
 */

int main ()
{
  vector_pro<int> myvector = { 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 };
  
  std::cout << "myvector contains:" << myvector << '\n';
  return 0;
}