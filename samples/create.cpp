# include "../vector_pro.hpp"
# include <vector>

/*
 * Output0: [ null ]
 * Output1: [ 100, 100, 100, 100, 100 ]
 * Output2: [ 100, 100, 100, 100, 100 ]
 * Output3: [ 100, 100, 100, 100, 100, 100, 100 ]
 * Output4: [ 100, 100, 100, 100, 100 ]
*/

int main() {
    
    std::cout << "Filepath: ./samples/create.cpp" << std::endl;
    
    vector_pro<int> test0;
    std::cout << "Output0: " << test0 << std::endl;
    
    vector_pro<int> test1(5, 100);
    std::cout << "Output1: " << test1 << std::endl;
    
    vector_pro<int> test2(test1);
    std::cout << "Output2: " << test2 << std::endl;

    std::vector<int> classic_vector(7, 100);
    vector_pro<int> test3(classic_vector);
    std::cout << "Output3: " << test3 << std::endl;

    const int int_array[] = {100, 100, 100, 100, 100};
    vector_pro<int> test4(int_array, std::size(int_array));
    std::cout << "Output4: " << test4 << std::endl;

    return 0;
}