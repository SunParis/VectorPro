# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/clear.cpp
 * ==================================
 * [ 100, 100, 100, 100, 100 ]
 * Size:      5
 * IsEmpty:   0
 * NotEmpty:  1
 * Capacity:  64
 * ==================================
 * [ null ]
 * Size:      0
 * IsEmpty:   1
 * NotEmpty:  0
 * Capacity:  64
 * ==================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/clear.cpp" << std::endl;
    std::cout << "==================================" << std::endl;

    vector_pro<int> test(5, 100);
    std::cout << test << std::endl;
    std::cout << "Size:      " << test.size() << std::endl;
    std::cout << "IsEmpty:   " << (bool)test.empty() << std::endl;
    std::cout << "NotEmpty:  " << (bool)test.not_empty() << std::endl;
    std::cout << "Capacity:  " << test.capacity() << std::endl;
    std::cout << "==================================" << std::endl;
    
    test.clear();
    std::cout << test << std::endl;
    std::cout << "Size:      " << test.size() << std::endl;
    std::cout << "IsEmpty:   " << (bool)test.empty() << std::endl;
    std::cout << "NotEmpty:  " << (bool)test.not_empty() << std::endl;
    std::cout << "Capacity:  " << test.capacity() << std::endl;
    std::cout << "==================================" << std::endl;

    return 0;
}