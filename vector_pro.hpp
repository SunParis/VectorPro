# pragma once

# ifndef null
# define null 0
# endif

# include <limits>
# include <stdio.h>
# include <iostream>
# include <string.h>
# include <exception>
# include <vector>

# ifndef VECTOR_DEFAULT_SIZE
# define VECTOR_DEFAULT_SIZE 64
# endif

# ifndef MYVECTOR
# define MYVECTOR 0

class vector_pro_exception: public std::exception {
private:
    char *str = null;
public:
    vector_pro_exception(const char *_str) {
        this->str = strdup(_str);
    }
    
    ~vector_pro_exception() override {
        if (this->str)  delete [] this->str;
        this->str = null;
    }
    
    const char* what() const throw() override {
        return this->str;
    }
};

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
    long int base = 0;
    long int end = 0;
    T **data = null;
    trash<T> *trash_head = null;
    
    void insertionSort(int left, int right, int(compare2)(const T &, const T &)) {
        T **arr = this->data;
        for (int i = left + 1; i <= right; i++) {
            T *temp = arr[i];
            int j = i - 1;
            while (j >= left && compare2(*(this->data[j]), *temp) > 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    void mergesort(int l, int m, int r, int(compare2)(const T &, const T &)) {
        T **arr = this->data;
        int len1 = m - l + 1, len2 = r - m;
        T **left = new T*[len1];
        T **right = new T*[len2];
    
        for (int i = 0; i < len1; i++)
            left[i] = arr[l + i];
        for (int i = 0; i < len2; i++)
            right[i] = arr[m + 1 + i];

        int i = 0, j = 0, k = l;
        while (i < len1 && j < len2) {
            if (compare2(*(left[i]), *(right[j])) <= 0) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < len1) {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < len2) {
            arr[k] = right[j];
            j++;
            k++;
        }

        delete [] left;
        delete [] right;
    }

public:
    
    vector_pro() {
        long int ini_size = VECTOR_DEFAULT_SIZE;
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
        }
        this->data = new T* [ini_size];
        if (this->data == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }
        this->curr_size = ini_size;
        this->end = 0;
    }
    
    vector_pro(std::vector<T> &another) {
        long int ini_size = another.capacity();
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
        }
        this->data = new T* [ini_size];
        if (this->data == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }
        this->curr_size = ini_size;
        this->end = 0;
        for (auto idx = another.begin(); idx < another.end(); idx++) {
            this->data[this->end] = new T(*idx);
            this->end++;
        }
    }

    vector_pro(const T *arr, const long int len) {
        long int ini_size = std::max<long int>(VECTOR_DEFAULT_SIZE, len);
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
        }
        this->data = new T* [ini_size];
        if (this->data == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }
        this->curr_size = ini_size;
        for (this->end = 0; this->end < len; this->end++) {
            this->data[this->end] = new T(arr + this->end);
        }
    }
    
    ~vector_pro() {
        if (this->data != null) {
            if (this->end > 0) {
                for (auto idx = 0; idx < this->end; idx++) {
                    delete this->data[idx];
                }
                this->end = 0;
            }
            delete [] this->data;
            this->data = null;
            this->curr_size = 0;
        }
        if (this->trash_head != null) {
            trash<T> *curr = this->trash_head;
            while (curr != null) {
                delete curr->data;
                this->trash_head = curr->next;
                delete curr;
                curr = this->trash_head;
            }
            this->trash_head = null;
        }
    }
    
    // Capacity
    
    long int size() {
        return this->end;
    }
    
    size_t max_size() {
        return std::numeric_limits<long int>::max();
    }
    
    void resize(const long int re_size) {
        if (re_size <= 0) {
            throw vector_pro_exception("Re_size val of vector should gt 0.");
        }
        if (re_size == this->curr_size) return;
        T **tmp = new T*[re_size];
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }
        if (re_size < this->curr_size) {
            for (auto idx = re_size; idx < this->end; idx++) {
                delete this->data[idx];
            }
            this->end = re_size;
        }
        for (auto idx = 0; idx < this->end; idx++) {
            tmp[idx] = this->data[idx];
        }
        delete [] this->data;
        this->data = tmp;
        return;
    }
    
    long int capacity() {
        return this->curr_size;
    }

    int empty() {
        if (this->end == 0) return 1;
        return 0;
    }
    
    void reserve(const long int re_size) {
        if (re_size <= 0) {
            throw vector_pro_exception("Re_size val of vector should gt 0.");
        }
        if (re_size < this->curr_size) return;
        T **tmp = new T*[re_size];
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }
        for (auto idx = 0; idx < this->end; idx++) {
            tmp[idx] = this->data[idx];
        }
        delete [] this->data;
        this->data = tmp;
        return;
    }
    
    void shrink_to_fit() {
        this->resize(this->end);
    }

    // Element access

    T& operator[](long int idx) {
        if (this->data == null || this->end <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->end) throw vector_pro_exception("Illegal index.");
        return *(this->data[idx]);
    }
    
    T& at(const long int idx) {
        if (this->data == null || this->end <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->end) throw vector_pro_exception("Illegal index.");
        return *(this->data[idx]);
    }

    T& front() {
        if (this->data == null || this->end <= 0) throw vector_pro_exception("Vector is empty.");
        return *(this->data[this->base]);
    }

    T& back() {
        return this->tail();
    }
    
    T& tail() {
        if (this->end <= 0) throw vector_pro_exception("Vector is empty.");
        return this->data[this->end - 1];
    }
    
    // Modifiers
    
    void assign(long int num, T& target) {
        // TODO
    }

    long int push_back(const T& target) {
        return this->push(target);
    }

    long int push(const T& target) {
        if (this->end == this->curr_size) {
            this->resize(this->curr_size * 2);
        }
        T *tmp = new T(target);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }        
        this->data[this->end] = tmp;
        this->end += 1;
        return (this->end - 1);
    }
    
    void pop_back() {
        if (this->end <= 0) throw vector_pro_exception("Vector is empty.");
        this->end--;
        delete this->data[this->end];
    }
    
    T& pop() {
        if (this->end <= 0) throw vector_pro_exception("Vector is empty.");
        T *ret = this->data[this->end];
        trash<T> *tmp = new trash<T>;
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }
        tmp->data = ret;
        tmp->next = this->trash_head;
        this->trash_head = tmp;
        this->end -= 1;
        return *ret;
    }
            
    void insert(long int idx, T& target) {
        // TODO
    }
        
    void swap(const long int idx1, const long int idx2) {
        if (this->data == null || this->end <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx1 >= this->end || idx2 >= this->end) throw vector_pro_exception("Illegal index.");
        if (idx1 < 0 || idx2 < 0) throw vector_pro_exception("Illegal index.");
        if (idx1 == idx2)   return;
        T *tmp = this->data[idx1];
        this->data[idx1] = this->data[idx2];
        this->data[idx2] = tmp;
    }
    
    void clear() {
        for (auto idx = 0; idx < this->end; idx++) {
            delete this->data[idx];
        }
        this->end = 0;
    }

    long int find(const T& target, int(compare2)(const T &, const T &)) {
        if (this->end <= 0) return -1;

        for (auto idx = 0; idx < this->end; idx++) {
            if (compare2(*(this->data[idx]), target) == 0)  return idx;
        }

        return -1;
    }
    
    void sort(int(compare2)(const T &, const T &)) {
        if (this->data == null || this->end <= 0) throw vector_pro_exception("Vector is empty.");
        const int RUN = 32;
        long int n = this->size();
        for (long int i = 0; i < n; i += RUN)
            insertionSort(i, (i + 31 < n - 1) ? (i + 31) : (n - 1), compare2);

        for (long int size = RUN; size < n; size = 2 * size) {
            for (long int left = 0; left < n; left += 2 * size) {
                long int mid = left + size - 1;
                long int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

                if (mid < right)
                    mergesort(left, mid, right, compare2);
            }
        }
    }
    
    void print(void(print)(T&)) {
        printf("[ ");
        for (auto idx = 0; idx < this->end; idx++) {
            print(*(this->data[idx]));
            if (idx < this->end - 1)    printf(", ");
        }
        printf(" ]");
    }

    void print(void(print)(void)) {
        printf("[ ");
        for (auto idx = 0; idx < this->end; idx++) {
            print();
            if (idx < this->end - 1)    printf(", ");
        }
        printf(" ]");
    }

    void print() {
        printf("[ ");
        for (auto idx = 0; idx < this->end; idx++) {
            std::cout << *(this->data[idx]);
            if (idx < this->end - 1)    printf(", ");
        }
        printf(" ]");
    }
    
    void merge(const vector_pro<T> &another) {
        // TODO
    }
};



# endif