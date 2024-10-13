
# include <iostream>
# include "vector_pro.hpp"
using namespace std;
static int _data = 0;

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector_pro<int> test1(a, 5);
    return 0;
}

