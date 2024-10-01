# include <iostream>
# include "my_vector.h"
using namespace std;

int func(const int &a, const int &b) {
    return a - b;
}

int main() {
    my_vector<int> A;
    // printf("?????\n");
    cout << A.length() << ", " << A.real_length() << endl;
    for (int i = 199; i >= 0; i--) {
        A.push(i);
    }
    for (int i = 30; i < 50; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
    cout << A.length() << ", " << A.real_length() << endl;
    try
    {
        cout << A[199] << endl;
    }
    catch(const char *e)
    {
        std::cerr << e << '\n';
    }
    cout << A.find(99, func) << endl;
    A.sort(func);
    for (int i = 30; i < 50; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
    return 0;
}

