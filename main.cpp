
# include <iostream>
# include "vector_pro.hpp"
using namespace std;
static int _data = 0;

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector_pro<int> test1(a, 5);
    vector_pro<int> test2(a + 5, 5);
    cout << "Before: " << test1 << endl;
    cout << "Before: " << test2 << endl;
    test1.assign(test2.begin() + 2, test2.end() - 1);
    cout << "After: " << test1 << endl;
    cout << "After: " << test2 << endl;
    return 0;
}

