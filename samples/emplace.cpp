# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/emplace.cpp
 * =========================================
 * test  ini: [ 0, 1, 2, 3, 4 ]
 * =========================================
 * Use emplace(position, target) to emplace 'taget' into the pos...
 * Running emplace(3, 100)
 * Before: [ 0, 1, 2, 3, 4 ]
 * After: [ 0, 1, 2, 100, 3, 4 ]
 * =========================================
 * Or use emplace(this_pos_iterator, target)...
 * Running emplace(test.begin() + 3, 200)
 * Before: [ 0, 1, 2, 100, 3, 4 ]
 * After: [ 0, 1, 2, 200, 100, 3, 4 ]
 * =========================================
 * Use emplace_back(target) to emplace 'taget' into the end...
 * Running emplace_back(777)
 * Before: [ 0, 1, 2, 200, 100, 3, 4 ]
 * After: [ 0, 1, 2, 200, 100, 3, 4, 777 ]
*/

int main() {
    
    std::cout << "Filepath: ./samples/emplace.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test;
    test.push(0);
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    std::cout << "test  ini: " << test << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use emplace(position, target) to emplace 'taget' into the pos..." << std::endl;
    std::cout << "Running emplace(3, 100)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.emplace(3, 100);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Or use emplace(this_pos_iterator, target)..." << std::endl;
    std::cout << "Running emplace(test.begin() + 3, 200)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.emplace(test.begin() + 3, 200);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use emplace_back(target) to emplace 'taget' into the end..." << std::endl;
    std::cout << "Running emplace_back(777)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.emplace_back(777);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}