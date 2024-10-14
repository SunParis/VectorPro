
# include <iostream>
# include <ctime>
# include "vector_pro.hpp"
using namespace std;
static int _data = 0;

class A {
public:
    int data[100];
    A() {
        this->data[0] = _data;
        _data++;
    }
    
    friend std::ostream& operator<<(std::ostream &output, const A& target) { 
        output << "{" << target.data << "}";
        return output;            
    }
};

int main() {
    auto classic_start = std::clock();
    vector<A> test;
    auto build_time = std::clock();
    for (int i = 0; i < 100; i++)   test.push_back(A());
    auto classic_end = std::clock();
    cout << "Ini time:: " << build_time - classic_start << endl;
    cout << "Time ::" << classic_end - build_time << endl;

    auto classic_start_2 = std::clock();
    vector_pro<A> test2;
    auto build_time2 = std::clock();
    for (int i = 0; i < 100; i++)   test2.push_back(A());
    auto classic_end_2 = std::clock();
    cout << "Ini time2:: " << build_time2 - classic_start_2 << endl;
    cout << "Time2 ::" << classic_end_2 - build_time2 << endl;
    return 0;
}

