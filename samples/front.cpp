// vector_pro::front
#include <iostream>
#include "../vector_pro.hpp"

/**
 * Output:
 * myvector.front() is now 62
 */

int main ()
{
  vector_pro<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';

  return 0;
}