
# include <iostream>
# include "vector_pro.hpp"
using namespace std;
static int _data = 0;

class A {
public:
    int data;
    A() {
        this->data = _data;
        _data++;
    }
    
    friend std::ostream& operator<<(std::ostream &output, const A& target) { 
        output << "{" << target.data << "}";
        return output;            
    }
};

int main() {
    vector_pro<A> test;
    for (int i = 0; i < 10; i++)    test.push_back(A());
    auto iter = test.rbegin();
    auto iter2 = const_iterator_pro<A>(iter);
    for ( ;iter2 != test.crend(); iter2++) {
        cout << *iter2 << ",";
    }
    cout << endl;
    return 0;
}

