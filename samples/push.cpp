// vector::push_back/push
#include <iostream>
#include "../vector_pro.h"

/**
 * The example uses push to add a new element to the vector each time a new integer is read.
 */

int main ()
{
  vector_pro<int> myvector;
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    myvector.push (myint);
  } while (myint);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

  return 0;
}