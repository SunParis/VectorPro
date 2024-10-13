# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/access_element.cpp
 * =========================================
 * [ 0, 1, 2, 3, 4 ]
 * =========================================
 * Use [index] to access an element ...
 * The 2nd element is 2
 * =========================================
 * Use at(index) to access an element ...
 * The 2nd element is 2
 * =========================================
 * Use front() to access the 1st element ...
 * The 1st element is 0
 * =========================================
 * Use tail() to access the last element ...
 * The last element is 4
 * =========================================
 * Use back to access the last element ...
 * The last element is 4
 * =========================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/access_element.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test;
    test.push(0);
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    std::cout << test << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use [index] to access an element ..." << std::endl;
    std::cout << "The 2nd element is " << test[2] << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use at(index) to access an element ..." << std::endl;
    std::cout << "The 2nd element is " << test.at(2) << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use front() to access the 1st element ..." << std::endl;
    std::cout << "The 1st element is " << test.front() << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use tail() to access the last element ..." << std::endl;
    std::cout << "The last element is " << test.tail() << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use back to access the last element ..." << std::endl;
    std::cout << "The last element is " << test.back() << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}