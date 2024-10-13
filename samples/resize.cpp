# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/resize.cpp
 * ==================================
 * [ 100, 100, 100, 100, 100 ]
 * Size:     5
 * MaxSize:  9223372036854775807
 * Capacity: 64
 * ==================================
 * After running reserve(70) ...
 * [ 100, 100, 100, 100, 100 ]
 * Size:     5
 * MaxSize:  9223372036854775807
 * Capacity: 70
 * ==================================
 * After running shrink_to_fit() ...
 * [ 100, 100, 100, 100, 100 ]
 * Size:     5
 * MaxSize:  9223372036854775807
 * Capacity: 5
 * ==================================
 * After running resize(3) ...
 * [ 100, 100, 100 ]
 * Size:     3
 * MaxSize:  9223372036854775807
 * Capacity: 3
 * ==================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/resize.cpp" << std::endl;
    std::cout << "==================================" << std::endl;

    vector_pro<int> test(5, 100);
    std::cout << test << std::endl;
    std::cout << "Size:     " << test.size() << std::endl;
    std::cout << "MaxSize:  " << test.max_size() << std::endl;
    std::cout << "Capacity: " << test.capacity() << std::endl;
    std::cout << "==================================" << std::endl;
    
    test.reserve(70);
    std::cout << "After running reserve(70) ..." << std::endl;
    std::cout << test << std::endl;
    std::cout << "Size:     " << test.size() << std::endl;
    std::cout << "MaxSize:  " << test.max_size() << std::endl;
    std::cout << "Capacity: " << test.capacity() << std::endl;
    std::cout << "==================================" << std::endl;

    test.shrink_to_fit();
    std::cout << "After running shrink_to_fit() ..." << std::endl;
    std::cout << test << std::endl;
    std::cout << "Size:     " << test.size() << std::endl;
    std::cout << "MaxSize:  " << test.max_size() << std::endl;
    std::cout << "Capacity: " << test.capacity() << std::endl;
    std::cout << "==================================" << std::endl;

    test.resize(3);
    std::cout << "After running resize(3) ..." << std::endl;
    std::cout << test << std::endl;
    std::cout << "Size:     " << test.size() << std::endl;
    std::cout << "MaxSize:  " << test.max_size() << std::endl;
    std::cout << "Capacity: " << test.capacity() << std::endl;
    std::cout << "==================================" << std::endl;

    return 0;
}