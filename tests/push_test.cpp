# include "../vector_pro.h"
# include "get_time.hpp"
# include "test_object.hpp"
# include "time_struct.hpp"
# include <iostream>
# include <fstream>
# define CLASSIC 0
# define PRO 1


using namespace std;

time_struct *push_test(std::size_t run, unsigned int test_data_size, bool first_flag) {
    time_struct *ret = new time_struct[2];
    test_object target(test_data_size);
    if (first_flag == true) {
        ret[CLASSIC].start = get_tick_count();
        vector<test_object> test;
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++)   test.push_back(target);
        ret[CLASSIC].end = get_tick_count();
        test.clear();
        ret[PRO].start = get_tick_count();
        vector_pro<test_object> test2;
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++)   test2.push_back(target);
        ret[PRO].end = get_tick_count();
        test2.clear();
    }
    else {
        ret[PRO].start = get_tick_count();
        vector_pro<test_object> test2;
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++)   test2.push_back(target);
        ret[PRO].end = get_tick_count();
        test2.clear();
        ret[CLASSIC].start = get_tick_count();
        vector<test_object> test;
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++)   test.push_back(target);
        ret[CLASSIC].end = get_tick_count();
        test.clear();
    }
    return ret;
}

int main() {
    
    unsigned int TIMES = 20;
    time_struct *res;
    fstream output_classic_build("./result/build_test_classic.txt", ofstream::out);
    fstream output_pro_build("./result/build_test_pro.txt", ofstream::out);
    fstream output_classic_run("./result/push_test_classic_run.txt", ofstream::out);
    fstream output_pro_run("./result/push_test_pro_run.txt", ofstream::out);
    for (int run = 1; run < 2000; run += 100) {
        for (int size = 1; size < 2000; size += 100) {
            write_struct out[2];
            for (int times = 0; times < (TIMES / 2); times++) {
                res = push_test(run, size, true);
                out[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
                out[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
                out[PRO].build_time += (res[PRO].build - res[PRO].start);
                out[PRO].run_time += (res[PRO].end - res[PRO].build);
                delete [] res;
            }
            for (int times = 0; times < (TIMES / 2); times++) {
                res = push_test(run, size, false);
                out[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
                out[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
                out[PRO].build_time += (res[PRO].build - res[PRO].start);
                out[PRO].run_time += (res[PRO].end - res[PRO].build);
                delete [] res;
            }
            output_classic_build << (size_t)(out[CLASSIC].build_time / ((TIMES / 2) * 2)) << " ";
            output_classic_run << (size_t)(out[CLASSIC].run_time / ((TIMES / 2) * 2)) << " ";
            output_pro_build << (size_t)(out[PRO].build_time / ((TIMES / 2) * 2)) << " ";
            output_pro_run << (size_t)(out[PRO].run_time / ((TIMES / 2) * 2)) << " ";
        }
        output_classic_build << "\n";
        output_classic_run << "\n";
        output_pro_build << "\n";
        output_pro_run << "\n";
        cout << "run " << run << " fin" << endl;
    }
    output_classic_build.close();
    output_classic_run.close();
    output_pro_build.close();
    output_pro_run.close();

    return 0;
}
