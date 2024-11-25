# define VECTOR_PRO_DEFAULT_SIZE 0
# include "../vector_pro.h"
# include "get_time.hpp"
# include "test_object.hpp"
# include "time_struct.hpp"
# include <iostream>
# include <fstream>
# define CLASSIC 0
# define PRO 1

using namespace std;

time_struct *traverse_test_1(size_t run, bool first_flag) {

    time_struct *ret = new time_struct[2];
    
    if (first_flag == true) {
        ret[CLASSIC].start = get_tick_count();
        vector<small_object> test;
        test.assign(100, small_object());
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test.begin(); iter != test.end(); iter++) {
                *iter;
            }
        }
        ret[CLASSIC].end = get_tick_count();
        test.clear();
        
        ret[PRO].start = get_tick_count();
        vector_pro<small_object> test2;
        test2.assign(100, small_object());
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test2.begin(); iter != test2.end(); iter++) {
                *iter;
            }
        }
        ret[PRO].end = get_tick_count();
        test2.clear();
    }
    else {
        
        ret[PRO].start = get_tick_count();
        vector_pro<small_object> test2;
        test2.assign(100, small_object());
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test2.begin(); iter != test2.end(); iter++) {
                *iter;
            }
        }
        ret[PRO].end = get_tick_count();
        test2.clear();
        
        ret[CLASSIC].start = get_tick_count();
        vector<small_object> test;
        test.assign(100, small_object());
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test.begin(); iter != test.end(); iter++) {
                *iter;
            }
        }
        ret[CLASSIC].end = get_tick_count();
        test.clear();
    }

    return ret;
}

time_struct *traverse_test_2(size_t run, bool first_flag) {

    time_struct *ret = new time_struct[2];
    
    if (first_flag == true) {
        ret[CLASSIC].start = get_tick_count();
        vector<medium_object> test;
        test.assign(100, medium_object());
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test.begin(); iter != test.end(); iter++) {
                *iter;
            }
        }
        ret[CLASSIC].end = get_tick_count();
        test.clear();
        
        ret[PRO].start = get_tick_count();
        vector_pro<medium_object> test2;
        test2.assign(100, medium_object());
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test2.begin(); iter != test2.end(); iter++) {
                *iter;
            }
        }
        ret[PRO].end = get_tick_count();
        test2.clear();
    }
    else {
        
        ret[PRO].start = get_tick_count();
        vector_pro<medium_object> test2;
        test2.assign(100, medium_object());
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test2.begin(); iter != test2.end(); iter++) {
                *iter;
            }
        }
        ret[PRO].end = get_tick_count();
        test2.clear();
        
        ret[CLASSIC].start = get_tick_count();
        vector<medium_object> test;
        test.assign(100, medium_object());
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test.begin(); iter != test.end(); iter++) {
                *iter;
            }
        }
        ret[CLASSIC].end = get_tick_count();
        test.clear();
    }

    return ret;
}

time_struct *traverse_test_3(size_t run, bool first_flag) {

    time_struct *ret = new time_struct[2];
    
    if (first_flag == true) {
        ret[CLASSIC].start = get_tick_count();
        vector<large_object> test;
        test.assign(100, large_object());
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test.begin(); iter != test.end(); iter++) {
                *iter;
            }
        }
        ret[CLASSIC].end = get_tick_count();
        test.clear();
        
        ret[PRO].start = get_tick_count();
        vector_pro<large_object> test2;
        test2.assign(100, large_object());
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test2.begin(); iter != test2.end(); iter++) {
                *iter;
            }
        }
        ret[PRO].end = get_tick_count();
        test2.clear();
    }
    else {
        
        ret[PRO].start = get_tick_count();
        vector_pro<large_object> test2;
        test2.assign(100, large_object());
        ret[PRO].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test2.begin(); iter != test2.end(); iter++) {
                *iter;
            }
        }
        ret[PRO].end = get_tick_count();
        test2.clear();
        
        ret[CLASSIC].start = get_tick_count();
        vector<large_object> test;
        test.assign(100, large_object());
        ret[CLASSIC].build = get_tick_count();
        for (int i = 0; i < run; i++) {
            for (auto iter = test.begin(); iter != test.end(); iter++) {
                *iter;
            }
        }
        ret[CLASSIC].end = get_tick_count();
        test.clear();
    }

    return ret;
}

int main() {
    
    unsigned int TIMES = 20;
    time_struct *res;
    fstream output_classic_run("./tests/results/traverse_test_classic_run.txt", ofstream::out);
    fstream output_pro_run("./tests/results/traverse_test_pro_run.txt", ofstream::out);
    for (int run = 1; run < 1000; run += 100) {
        
        write_struct out[2];
        for (int times = 0; times < (TIMES / 2); times++) {
            res = traverse_test_1(run, true);
            out[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
            out[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
            out[PRO].build_time += (res[PRO].build - res[PRO].start);
            out[PRO].run_time += (res[PRO].end - res[PRO].build);
            delete [] res;
        }
        for (int times = 0; times < (TIMES / 2); times++) {
            res = traverse_test_1(run, false);
            out[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
            out[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
            out[PRO].build_time += (res[PRO].build - res[PRO].start);
            out[PRO].run_time += (res[PRO].end - res[PRO].build);
            delete [] res;
        }
        output_classic_run << (size_t)(out[CLASSIC].run_time / ((TIMES / 2) * 2)) << " ";
        output_pro_run << (size_t)(out[PRO].run_time / ((TIMES / 2) * 2)) << " ";

        write_struct out_2[2];
        for (int times = 0; times < (TIMES / 2); times++) {
            res = traverse_test_2(run, true);
            out_2[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
            out_2[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
            out_2[PRO].build_time += (res[PRO].build - res[PRO].start);
            out_2[PRO].run_time += (res[PRO].end - res[PRO].build);
            delete [] res;
        }
        for (int times = 0; times < (TIMES / 2); times++) {
            res = traverse_test_2(run, false);
            out_2[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
            out_2[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
            out_2[PRO].build_time += (res[PRO].build - res[PRO].start);
            out_2[PRO].run_time += (res[PRO].end - res[PRO].build);
            delete [] res;
        }
        output_classic_run << (size_t)(out_2[CLASSIC].run_time / ((TIMES / 2) * 2)) << " ";
        output_pro_run << (size_t)(out_2[PRO].run_time / ((TIMES / 2) * 2)) << " ";
        
        write_struct out_3[2];
        for (int times = 0; times < (TIMES / 2); times++) {
            res = traverse_test_3(run, true);
            out_3[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
            out_3[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
            out_3[PRO].build_time += (res[PRO].build - res[PRO].start);
            out_3[PRO].run_time += (res[PRO].end - res[PRO].build);
            delete [] res;
        }
        for (int times = 0; times < (TIMES / 2); times++) {
            res = traverse_test_3(run, false);
            out_3[CLASSIC].build_time += (res[CLASSIC].build - res[CLASSIC].start);
            out_3[CLASSIC].run_time += (res[CLASSIC].end - res[CLASSIC].build);
            out_3[PRO].build_time += (res[PRO].build - res[PRO].start);
            out_3[PRO].run_time += (res[PRO].end - res[PRO].build);
            delete [] res;
        }
        output_classic_run << (size_t)(out_3[CLASSIC].run_time / ((TIMES / 2) * 2)) << " ";
        output_pro_run << (size_t)(out_3[PRO].run_time / ((TIMES / 2) * 2)) << " ";

        output_classic_run << "\n";
        output_pro_run << "\n";
        cout << "run " << run << " fin" << endl;
    }

    output_classic_run.close();
    output_pro_run.close();
    
    return 0;
}
