// comparing size, capacity and max_size
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * size: 100
 * capacity: 128
 * max_size: 9223372036854775807
 */


int main ()
{
  vector_pro<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << (int) myvector.size() << '\n';
  std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  std::cout << "max_size: " << (std::size_t) myvector.max_size() << '\n';
  return 0;
}