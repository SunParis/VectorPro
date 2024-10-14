# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/erase.cpp
 * =========================================
 * test  ini: [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
 * =========================================
 * Use erase(position) to erase the element at position...
 * Running erase(1)
 * Before: [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
 * After: [ 0, 2, 3, 4, 5, 6, 7, 8, 9 ]
 * =========================================
 * Or Use erase(this_iter_pos)...
 * Running erase(test.begin() + 1)
 * Before: [ 0, 2, 3, 4, 5, 6, 7, 8, 9 ]
 * After: [ 0, 3, 4, 5, 6, 7, 8, 9 ]
 * =========================================
 * Use erase(from_pos, exclude_pos) to erase the element at in[from_pos, exclude_pos)...
 * Running erase(1, 3)
 * Before: [ 0, 3, 4, 5, 6, 7, 8, 9 ]
 * After: [ 0, 5, 6, 7, 8, 9 ]
 * =========================================
 * Or use erase(this_from_pos_iter, this_exclude_pos_iter)...
 * Running erase(test.begin() + 1, test.begin() + 3)
 * Before: [ 0, 5, 6, 7, 8, 9 ]
 * After: [ 0, 7, 8, 9 ]
 * =========================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/erase.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test;
    test.push(0);
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    test.push(5);
    test.push(6);
    test.push(7);
    test.push(8);
    test.push(9);
    std::cout << "test  ini: " << test << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use erase(position) to erase the element at position..." << std::endl;
    std::cout << "Running erase(1)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.erase(1);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Or Use erase(this_iter_pos)..." << std::endl;
    std::cout << "Running erase(test.begin() + 1)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.erase(test.begin() + 1);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use erase(from_pos, exclude_pos) to erase the element at in[from_pos, exclude_pos)..." << std::endl;
    std::cout << "Running erase(1, 3)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.erase(1, 3);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;    

    std::cout << "Or use erase(this_from_pos_iter, this_exclude_pos_iter)..." << std::endl;
    std::cout << "Running erase(test.begin() + 1, test.begin() + 3)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.erase(test.begin() + 1, test.begin() + 3);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}