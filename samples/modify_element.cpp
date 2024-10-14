# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/modify_element.cpp
 * =========================================
 * [ 0, 1, 2, 3, 4 ]
 * =========================================
 * Use [index] to modify an element ...
 * Running test[2] = 777
 * [2] Before: 2
 * [2] After: 777
 * =========================================
 * Use at(index) to modify an element ...
 * Running test.at(3) = 777
 * [3] Before: 3
 * [3] After: 777
 * =========================================
 * Use front() to modify an element ...
 * Running test.front() = 777
 * [0] Before: 0
 * [0] After: 777
 * =========================================
 * Use back() to modify an element ...
 * Running test.back() = 777
 * [4] Before: 4
 * [4] After: 777
 * =========================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/modify_element.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test;
    test.push(0);
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    std::cout << test << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use [index] to modify an element ..." << std::endl;
    std::cout << "Running test[2] = 777" << std::endl;
    std::cout << "[2] Before: " << test[2] << std::endl;
    test[2] = 777;
    std::cout << "[2] After: " << test[2] << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use at(index) to modify an element ..." << std::endl;
    std::cout << "Running test.at(3) = 777" << std::endl;
    std::cout << "[3] Before: " << test[3] << std::endl;
    test.at(3) = 777;
    std::cout << "[3] After: " << test[3] << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use front() to modify an element ..." << std::endl;
    std::cout << "Running test.front() = 777" << std::endl;
    std::cout << "[0] Before: " << test[0] << std::endl;
    test.front() = 777;
    std::cout << "[0] After: " << test[0] << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use back() to modify an element ..." << std::endl;
    std::cout << "Running test.back() = 777" << std::endl;
    std::cout << "[4] Before: " << test[4] << std::endl;
    test.back() = 777;
    std::cout << "[4] After: " << test[4] << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}