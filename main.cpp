
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
    vector_pro<A> test2;
    for (int i = 0; i < 10; i++)    test.push_back(A());
    for (int i = 0; i < 10; i++)    test2.push_back(A());
    cout << test << endl;
    cout << test2 << endl;
    test = test2;
    test2.clear();
    cout << test << endl;
    cout << test2 << endl;
    return 0;
}

