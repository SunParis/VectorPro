# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/insert.cpp
 * =========================================
 * test  ini: [ 0, 1, 2, 3, 4 ]
 * test2 ini: [ 0, 1, 2, 3, 4 ]
 * =========================================
 * Use insert(position, target) to insert 'taget' into the pos...
 * Running insert(3, 100)
 * Before: [ 0, 1, 2, 3, 4 ]
 * After: [ 0, 1, 2, 100, 3, 4 ]
 * =========================================
 * Or use insert(this_pos_iterator, target)...
 * Running insert(test.begin() + 3, 200)
 * Before: [ 0, 1, 2, 100, 3, 4 ]
 * After: [ 0, 1, 2, 200, 100, 3, 4 ]
 * =========================================
 * Or use insert(this_pos_iterator, other_iterator_from other_iterator_exclude_to)...
 * Running insert(test2.begin() + 2, test.begin() + 1, test.end() - 1)
 * Before: [ 0, 1, 2, 3, 4 ]
 * After: [ 0, 1, 1, 2, 200, 100, 3, 2, 3, 4 ]
 * =========================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/insert.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test;
    test.push(0);
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    vector_pro<int> test2(test);
    std::cout << "test  ini: " << test << std::endl;
    std::cout << "test2 ini: " << test2 << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use insert(position, target) to insert 'taget' into the pos..." << std::endl;
    std::cout << "Running insert(3, 100)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.insert(3, 100);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Or use insert(this_pos_iterator, target)..." << std::endl;
    std::cout << "Running insert(test.begin() + 3, 200)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.insert(test.begin() + 3, 200);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Or use insert(this_pos_iterator, other_iterator_from, other_iterator_exclude_to)..." << std::endl;
    std::cout << "Running insert(test2.begin() + 2, test.begin() + 1, test.end() - 1)" << std::endl;
    std::cout << "Before: " << test2 << std::endl;
    test2.insert(test2.begin() + 2, test.begin() + 1, test.end() - 1);
    std::cout << "After: " << test2 << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}