// constructing vectors
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * The contents of fifth are: [ 100, 100, 100, 100 ]
 * While in fourth will be: [ null ]
 */

int main () {
  // constructors used in the same order as described above:
  
  // empty vector_pro of ints
  vector_pro<int> first;     

  // four ints with value 100
  vector_pro<int> second (4,100);                       
  
  // iterating through second
  vector_pro<int> third (second.begin(),second.end());  
  
  // a copy of third
  vector_pro<int> fourth (third);

  // a `move` from fourth
  vector_pro<int> fifth (std::move(fourth));
  std::cout << "The contents of fifth are: " << fifth << std::endl;
  std::cout << "While in fourth will be: " << fourth << std::endl;
  
  // a copy from std::vector
  std::vector<int> myints = {1, 2, 3, 4, 5};
  vector_pro<int> sixth (myints);
  
  // a copy from initializer list
  vector_pro<int> seventh = {1, 2, 3, 4, 5};

  // a copy from initializer list
  int arr[5] = {0, 1, 2, 3, 4};
  vector_pro<int> eighth (arr, 5);

  return 0;
}