// vector_pro assign
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * Size of first: 7
 * Size of second: 5
 * Size of third: 3
 */

int main ()
{
  vector_pro<int> first;
  vector_pro<int> second;
  vector_pro<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  iterator_pro<int> it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  third.assign ({1, 2, 3});   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
  return 0;
}