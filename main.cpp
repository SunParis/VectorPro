// # include <vector>
# include <iostream>
# include "vector_pro.hpp"
using namespace std;

int main() {
    vector_pro<int> A;
    for (int i = 0; i < 15; i++) {
        A.push_back(i);
    }
    auto lambda_print = [](int& i) {
        printf("%d", i);
    };
    void (*print_func)(int&) = lambda_print;
    A.print_list(print_func);
    
    cout << endl;
    return 0;
}

