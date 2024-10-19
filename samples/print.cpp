// vector_pro::print
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains: [ 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 ]
 */

int main ()
{
  vector_pro<int> myvector = { 32, 72, 55, 46, 32, 12, 61, 84, 39, 97 };
  
  // print
  std::cout << "myvector contains: ";
  myvector.print();
  std::cout << std::endl;
  return 0;
}