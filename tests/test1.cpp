# include "../vector_pro.h"
# include <iostream>
# include "get_time.hpp"

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
    size_t TOTAL_RUN = 10000;

    cout << "TOTAL_RUN     :: " << TOTAL_RUN << endl;
    auto start_1 = get_tick_count();
    vector<big_obj> test;
    auto build_1 = get_tick_count();
    for (int i = 0; i < TOTAL_RUN; i++)   test.push_back(big_obj());
    auto end_1 = get_tick_count();
    cout << "Ini time  (ns):: " << build_1 - start_1 << endl;
    cout << "Time      (ns):: " << end_1 - build_1 << endl;
    cout << "Total1    (ns):: " << end_1 - start_1 << endl;

    auto start_2 = get_tick_count();
    vector_pro<big_obj> test2;
    auto build_2 = get_tick_count();
    for (int i = 0; i < TOTAL_RUN; i++)   test2.push_back(big_obj());
    auto end_2 = get_tick_count();
    cout << "Ini time2 (ns):: " << build_2 - start_2 << endl;
    cout << "Time2     (ns):: " << end_2 - build_2 << endl;
    cout << "Total2    (ns):: " << end_2 - start_2 << endl;
    return 0;
}
