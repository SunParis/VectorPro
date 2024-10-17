# include "../vector_pro.h"

/*
 * Filepath: ./samples/push_pop.cpp
 * =========================================
 * test  ini: [ null ]
 * =========================================
 * Use push(...) / push_bask(...) to push sth into vector...
 * Running push(777)
 * Before: [ null ]
 * After: [ 777 ]
 * =========================================
 * Use pop(...) to pop out sth from vector (has ret value!)...
 * Running pop()
 * Before: [ 777 ]
 * After: [ null ]
 * Return: 777
 * =========================================
 * Or use pop_back(...) to pop out sth from vector (has no ret)...
 * Running pop_back()
 * Before: [ 777 ]
 * After: [ null ]
 * =========================================
*/

int main() {
    
    std::cout << "Filepath: ./samples/push_pop.cpp" << std::endl;
    std::cout << "=========================================" << std::endl;

    vector_pro<int> test;
    std::cout << "test  ini: " << test << std::endl;
    std::cout << "=========================================" << std::endl;
    
    std::cout << "Use push(...) / push_bask(...) to push sth into vector..." << std::endl;
    std::cout << "Running push(777)" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.push(777);
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Use pop(...) to pop out sth from vector (has ret value!)..." << std::endl;
    std::cout << "Running pop()" << std::endl;
    std::cout << "Before: " << test << std::endl;
    int ret = test.pop();
    std::cout << "After: " << test << std::endl;
    std::cout << "Return: " << ret << std::endl;
    std::cout << "=========================================" << std::endl;

    test.push(777);
    std::cout << "Or use pop_back(...) to pop out sth from vector (has no ret)..." << std::endl;
    std::cout << "Running pop_back()" << std::endl;
    std::cout << "Before: " << test << std::endl;
    test.pop_back();
    std::cout << "After: " << test << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}