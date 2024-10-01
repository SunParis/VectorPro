# ifndef MYVECTOR
# define MYVECTOR 0

# include <stdio.h>
# ifndef null
# define null 0
# endif

template <typename T>
class trash {
public:
    T *data;
    trash<T> *next = null;
};

template <typename T>
class vector_pro {
private:
    long int curr_size = 0;
    long int end = 0;
    T **data = null;
    trash<T> *trash_head = null;
    void insertionSort(int left, int right, int(compare2)(const T &, const T &));
    void mergesort(int l, int m, int r, int(compare2)(const T &, const T &));
public:
    vector_pro(const long int ini_size = 128);
    ~vector_pro();
    void clean();
    int empty();
    T& at(const long int idx);
    long int push(const T& target);
    T& pop();
    T& tail();
    long int length();
    long int capacity();
    long int find(const T& target, int(compare2)(const T &, const T &));
    void resize(const long int re_size);
    T& operator[](long int idx);    
    void swap(const long int idx1, const long int idx2);
    void sort(int(compare2)(const T&, const T&));
    void merge(const vector_pro<T> &another);
};

# include "vector_pro.cpp"

# endif