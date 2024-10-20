
# include <iostream>
# include "vector_pro.h"

using namespace std;


int main() {
    
    vector_pro<char> myvector("Hello World!", sizeof("Hello World!"));

    cout << myvector << endl;

    vector_pro<int> test;
    test.assign(10, 100);
    vector_pro<int>test2(test.begin(), test.end());

    return 0;
}

