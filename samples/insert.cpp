// inserting into a vector_pro
#include <iostream>
#include "../vector_pro.h"

/**
 * Output:
 * myvector contains: 501 502 503 300 300 400 400 200 100 100 100
 */

int main ()
{
  vector_pro<int> myvector (3,100);
  iterator_pro<int> it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  vector_pro<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  std::initializer_list<int> myarray = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it != myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}