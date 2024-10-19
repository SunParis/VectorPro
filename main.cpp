
# include <iostream>
# include "vector_pro.h"

using namespace std;


int main() {
    
    vector_pro<char> myvector("Hello World!", sizeof("Hello World!"));

    cout << myvector << endl;

    return 0;
}

