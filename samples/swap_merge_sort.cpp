# include "../vector_pro.hpp"

/*
 * Filepath: ./samples/swap_merge_sort.cpp
 * =========================================
 * test  ini: [ 0, 2, 4, 6, 8 ]
 * test2 ini: [ 1, 3, 5, 7, 9 ]
 * =========================================
 * Use swap(pos1, pos2) to swap the element at pos1 and pos2...
 * Running swap(0, 2)
 * Before: [ 0, 2, 4, 6, 8 ]
 * After: [ 4, 2, 0, 6, 8 ]
 * =========================================
 * Use swap(another_vector_pro) to swap the two vectors...
 * Running swap(test2)
 * Before:  [ 4, 2, 0, 6, 8 ]
 * Before2: [ 1, 3, 5, 7, 9 ]
 * After:  [ 1, 3, 5, 7, 9 ]
 * After2: [ 4, 2, 0, 6, 8 ]
 * =========================================
 * Use merge(another_vector_pro) to merge the other vector to the end of curr...
 * Running merge(test2)
 * Before:  [ 1, 3, 5, 7, 9 ]
 * Before2: [ 4, 2, 0, 6, 8 ]
 * After:  [ 1, 3, 5, 7, 9, 4, 2, 0, 6, 8 ]
 * After2: [ 4, 2, 0, 6, 8 ]
 * =========================================
 * Use sort() to sort the vector...
 * * Be sure '>' and '<' defined before compiling.
 * Running sort()
 * Before: [ 1, 3, 5, 7, 9, 4, 2, 0, 6, 8 ]
 * After: [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
 * =========================================
 * Or use sort(int(compare_to)(const T &, const T &))...
 * Running sort(compare2)
 * Before: [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
 * After: [ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 ]
 * =========================================
 * Use reverse() to reverse the vector...
 * Running reverse()
 * Before: [ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 ]
 * After: [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
 * =========================================
*/

int compare2(const int& a, const int& b) {
    return b - a;
}

int main() {
    
    std::cout << "Filepath: ./samples/swap_merge_sort.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test, test2;
    test.push(0);
    test2.push(1);
    test.push(2);
    test2.push(3);
    test.push(4);
    test2.push(5);
    test.push(6);
    test2.push(7);
    test.push(8);
    test2.push(9);
    std::cout << "test  ini: " << test << std::endl;
    std::cout << "test2 ini: " << test2 << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use swap(pos1, pos2) to swap the element at pos1 and pos2..." << std::endl;
    std::cout << "Running swap(0, 2)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.swap(0, 2);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use swap(another_vector_pro) to swap the two vectors..." << std::endl;
    std::cout << "Running swap(test2)" << std::endl;
    std::cout << "Before:  " << test << std::endl;
    std::cout << "Before2: " << test2 << std::endl;
    test.swap(test2);
    std::cout << "After:  " << test << std::endl;
    std::cout << "After2: " << test2 << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use merge(another_vector_pro) to merge the other vector to the end of curr..." << std::endl;
    std::cout << "Running merge(test2)" << std::endl;
    std::cout << "Before:  " << test << std::endl;
    std::cout << "Before2: " << test2 << std::endl;
    test.merge(test2);
    std::cout << "After:  " << test << std::endl;
    std::cout << "After2: " << test2 << std::endl;
    std::cout << "=========================================" << std::endl;    

    std::cout << "Use sort() to sort the vector..." << std::endl;
    std::cout << "* Be sure '>' and '<' defined before compiling." << std::endl;
    std::cout << "Running sort()" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.sort();
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Or use sort(int(compare_to)(const T &, const T &))..." << std::endl;
    std::cout << "Running sort(compare2)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.sort(compare2);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use reverse() to reverse the vector..." << std::endl;
    std::cout << "Running reverse()" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.reverse();
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}