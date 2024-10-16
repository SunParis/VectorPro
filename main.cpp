
# include <iostream>
# include <ctime>
# include "vector_pro.hpp"
using namespace std;
static int _data = 0;

class small_obj {
public:
    int data[100];
    small_obj() {
        this->data[0] = _data;
        _data++;
    }
    
    friend std::ostream& operator<<(std::ostream &output, const small_obj& target) { 
        output << "# " << target.data[0] << " ...";
        return output;            
    }
};

class big_obj {
public:
    byte data;
    big_obj() {
        this->data = (byte)_data;
        _data++;
    }
    
    friend std::ostream& operator<<(std::ostream &output, const big_obj& target) { 
        output << "# " << (int)target.data;
        return output;            
    }
};


int main() {
    
    /*auto classic_start = std::clock();
    vector<big_obj> test;
    auto build_time = std::clock();
    for (int i = 0; i < 100; i++)   test.push_back(big_obj());
    auto classic_end = std::clock();
    cout << "Ini time:: " << build_time - classic_start << endl;
    cout << "Time ::" << classic_end - build_time << endl;

    auto classic_start_2 = std::clock();
    vector_pro<big_obj> test2;
    auto build_time2 = std::clock();
    for (int i = 0; i < 100; i++)   test2.push_back(big_obj());
    auto classic_end_2 = std::clock();
    cout << "Ini time2:: " << build_time2 - classic_start_2 << endl;
    cout << "Time2 ::" << classic_end_2 - build_time2 << endl;
    */
    vector_pro<int> A, B;
    A.push(10);
    B.push(9);
    A.swap(A.begin(), B.begin());
    cout << A << endl;
    cout << B << endl;
    return 0;
}

