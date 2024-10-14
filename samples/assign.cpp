# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/assign.cpp
 * =========================================
 * test  ini: [ null ]
 * test2 ini: [ null ]
 * =========================================
 * Use assign(...) to initial...
 * Running assign(5, 777)
 * Before: [ null ]
 * After: [ 777, 777, 777, 777, 777 ]
 * =========================================
 * Use assign(...) to modify...
 * Running assign(2, 666)
 * Before: [ 777, 777, 777, 777, 777 ]
 * After: [ 666, 666, 777, 777, 777 ]
 * =========================================
 * Another way to use assign(...) ...
 * Running test2.assign(test.begin() + 1, test.end() - 1)
 * Before: [ null ]
 * After: [ 666, 777, 777 ]
 * =========================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/assign.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test, test2;
    std::cout << "test  ini: " << test << std::endl;
    std::cout << "test2 ini: " << test2 << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use assign(...) to initial..." << std::endl;
    std::cout << "Running assign(5, 777)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.assign(5, 777);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use assign(...) to modify..." << std::endl;
    std::cout << "Running assign(2, 666)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.assign(2, 666);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Another way to use assign(...) ..." << std::endl;
    std::cout << "Running test2.assign(test.begin() + 1, test.end() - 1)" << std::endl;
    std::cout << "Before: " << test2 << std::endl;
    test2.assign(test.begin() + 1, test.end() - 1);
    std::cout << "After: " << test2 << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}