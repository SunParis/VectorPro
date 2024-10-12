
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
        //cout << this->data << " being created." << endl;
    }
    A(const A& ano) {
        this->data = ano.data;
        //cout << this->data << " being copied." << endl;
    }
    ~A() {
        //cout << this->data << " being destroyed." << endl;
    }
    
    friend ostream &operator<<( ostream &output, const A &target ) { 
        output << target.data;
        return output;            
    }
};

int main() {
    vector_pro<A> test;
    A data[10];
    for (auto idx = 0; idx < 10; idx++) {
        test.push_back(data[idx]);
    }
    cout << test << endl;

    test[5] = A();
    for (auto iter = test.begin(); iter != test.end(); iter++) {
        cout << *iter;
    }
    cout << endl;
    
    cout << test << endl;
    return 0;
}

