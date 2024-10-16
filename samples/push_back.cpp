// vector::push_back/push
#include <iostream>
#include "../vector_pro.hpp"

/**
 * The example uses push_back to add a new element to the vector each time a new integer is read.
 */

int main ()
{
  vector_pro<int> myvector;
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    myvector.push_back (myint);
  } while (myint);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

  return 0;
}