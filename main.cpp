// # include <vector>
# include <iostream>
# include "vector_pro.hpp"
# include <vector>
using namespace std;


int main() {
    vector_pro<int> A, B;
    A.merge(B);
    vector<int> C;
    C.assign(7, 10);
    return 0;
}

