# pragma once

# ifndef null
# define null 0
# endif

# include <cstdint>
# include <limits>
# include <stdio.h>
# include <iostream>
# include <string.h>
# include <exception>
# include <vector>

# ifndef VECTOR_PRO_DEFAULT_SIZE
# define VECTOR_PRO_DEFAULT_SIZE 64
# endif

# ifndef VECTOR_PRO
# define VECTOR_PRO 1

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
class iterator_pro {
private:
    T **data = null;
    int64_t curr_pos = 0;
public:
    iterator_pro(T **source, int64_t idx = 0) {
        this->data = source;
        this->curr_pos = idx;
    }
    
    int64_t get_idx() const {
        return this->curr_pos;
    }

    T **get_data() const {
        return this->data;
    }
    
    iterator_pro operator++() {
        return iterator_pro(this->data, this->curr_pos + 1);
    }

    iterator_pro operator++(int) {
        iterator_pro<T> ret(this->data, this->curr_pos);
        this->curr_pos++;
        return ret;
    }
    
    iterator_pro operator--() {
        return iterator_pro(this->data, this->curr_pos - 1);
    }

    iterator_pro operator--(int) {
        iterator_pro<T> ret(this->data, this->curr_pos);
        this->curr_pos--;
        return ret;
    }

    bool operator==(const iterator_pro<T>& another) const {
        size_t A = (size_t)this->data;
        size_t B = (size_t)another.get_data();
        return ((A == B) && (this->curr_pos == another.get_idx()));
    }

    bool operator!=(const iterator_pro<T>& another) const {
        size_t A = (size_t)this->data;
        size_t B = (size_t)another.get_data();
        return ((A != B) || (this->curr_pos != another.get_idx()));
    }

    T& operator*() {
        return *(this->data[curr_pos]);
    }
};

template <typename T>
class vector_pro {
private:
    int64_t curr_size = 0;
    int64_t data_len = 0;
    T **data = null;
    
    void insertionSort(int64_t left, int64_t right, int(compare2)(const T &, const T &)) {
        T **arr = this->data;
        for (int64_t i = left + 1; i <= right; i++) {
            T *temp = arr[i];
            int64_t j = i - 1;
            while (j >= left && compare2(*(this->data[j]), *temp) > 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    void mergesort(int64_t l, int64_t m, int64_t r, int(compare2)(const T &, const T &)) {
        T **arr = this->data;
        int64_t len1 = m - l + 1, len2 = r - m;
        T **left = new T*[len1];
        T **right = new T*[len2];
    
        for (int64_t i = 0; i < len1; i++)
            left[i] = arr[l + i];
        for (int64_t i = 0; i < len2; i++)
            right[i] = arr[m + 1 + i];

        int64_t i = 0, j = 0, k = l;
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
        int64_t ini_size = VECTOR_PRO_DEFAULT_SIZE;
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
            return;
        }
        this->data = new T* [ini_size];
        if (this->data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = 0;
    }
    
    vector_pro(std::vector<T> &another) {
        int64_t ini_size = another.capacity();
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
            return;
        }
        this->data = new T* [ini_size];
        if (this->data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = 0;
        for (auto idx = another.begin(); idx < another.data_len(); idx++) {
            this->data[this->data_len] = new T(*idx);
            this->data_len++;
        }
    }

    vector_pro(const T *arr, const int64_t len) {
        int64_t ini_size = std::max<int64_t>(VECTOR_PRO_DEFAULT_SIZE, len);
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
            return;
        }
        this->data = new T* [ini_size];
        if (this->data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        for (this->data_len = 0; this->data_len < len; this->data_len++) {
            this->data[this->data_len] = new T(arr + this->data_len);
        }
    }
    
    ~vector_pro() {
        if (this->data != null) {
            if (this->data_len > 0) {
                for (int64_t idx = 0; idx < this->data_len; idx++) {
                    delete this->data[idx];
                }
                this->data_len = 0;
            }
            delete [] this->data;
            this->data = null;
            this->curr_size = 0;
        }
    }
    
    // Capacity
    
    int64_t size() const {
        return this->data_len;
    }
    
    size_t max_size() const {
        return std::numeric_limits<int64_t>::max();
    }
    
    void resize(const int64_t re_size) {
        if (re_size <= 0) {
            throw vector_pro_exception("Resize val of vector should gt 0.");
            return;
        }
        if (re_size == this->curr_size) return;
        T **tmp = new T*[re_size];
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        if (re_size < this->curr_size) {
            for (int64_t idx = re_size; idx < this->data_len; idx++) {
                delete this->data[idx];
            }
            this->data_len = re_size;
        }
        for (int64_t idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->data[idx];
        }
        delete [] this->data;
        this->data = tmp;
        return;
    }
    
    int64_t capacity() const {
        return this->curr_size;
    }

    bool empty() const {
        if (this->data_len == 0) return true;
        return false;
    }

    bool not_empty() const {
        return !(this->empty());
    }
    
    void reserve(const int64_t re_size) {
        if (re_size <= 0) {
            throw vector_pro_exception("Re_size val of vector should gt 0.");
            return;
        }
        if (re_size < this->curr_size) return;
        T **tmp = new T*[re_size];
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
            return;
        }
        for (int64_t idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->data[idx];
        }
        delete [] this->data;
        this->data = tmp;
        return;
    }
    
    void shrink_to_fit() {
        this->resize(this->data_len);
    }

    // Element access

    T& operator[](int64_t idx) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->data_len) throw vector_pro_exception("Illegal index.");
        return *(this->data[idx]);
    }
    
    T& at(const int64_t idx) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->data_len) throw vector_pro_exception("Illegal index.");
        return *(this->data[idx]);
    }

    T& front() {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        return *(this->data[this->base]);
    }

    T& back() {
        return this->tail();
    }
    
    T& tail() {
        if (this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        return this->data[this->data_len - 1];
    }
    
    // Modifiers
    
    void assign(int64_t num, T& target) {
        // TODO
    }

    int64_t push_back(const T& target) {
        
        return this->push(target);
    }

    int64_t push(const T& target) {
        if (this->data_len == this->curr_size) {
            this->resize(this->curr_size * 2);
        }
        T *tmp = new T(target);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }        
        this->data[this->data_len] = tmp;
        this->data_len += 1;
        return (this->data_len - 1);
    }
    
    void pop_back() {
        if (this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        this->data_len--;
        delete this->data[this->data_len];
    }
    
    T pop() {
        if (this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        T ret = T(*this->data[this->data_len]);
        delete [] this->data[this->data_len];
        this->data_len -= 1;
        return ret;
    }
            
    void insert(int64_t idx, T& target) {
        // TODO
    }
        
    void swap(const int64_t idx1, const int64_t idx2) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx1 >= this->data_len || idx2 >= this->data_len) throw vector_pro_exception("Illegal index.");
        if (idx1 < 0 || idx2 < 0) throw vector_pro_exception("Illegal index.");
        if (idx1 == idx2)   return;
        T *tmp = this->data[idx1];
        this->data[idx1] = this->data[idx2];
        this->data[idx2] = tmp;
    }
    
    void clear() {
        for (int64_t idx = 0; idx < this->data_len; idx++) {
            delete this->data[idx];
        }
        this->data_len = 0;
    }

    int64_t find(const T& target, int(compare2)(const T &, const T &), int64_t from = 0, int64_t to = -1) {
        if (this->data_len <= 0) return -1;

        if (to == -1) to = this->data_len;
        if (to < from) {
            int64_t tmp = from;
            from = to;
            to = tmp;
        }

        for (int64_t idx = from; idx < to; idx++) {
            if (compare2(*(this->data[idx]), target) == 0)  return idx;
        }

        return -1;
    }
    
    void sort(int(compare2)(const T &, const T &)) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        const int RUN = 32;
        int64_t n = this->size();
        for (int64_t i = 0; i < n; i += RUN)
            insertionSort(i, (i + 31 < n - 1) ? (i + 31) : (n - 1), compare2);

        for (int64_t size = RUN; size < n; size = 2 * size) {
            for (int64_t left = 0; left < n; left += 2 * size) {
                int64_t mid = left + size - 1;
                int64_t right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

                if (mid < right)
                    mergesort(left, mid, right, compare2);
            }
        }
    }
    
    void print(void(print)(T&)) {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            print(*(this->data[idx]));
            if (idx < this->data_len - 1)    printf(", ");
        }
        printf(" ]");
    }

    void print(void(print)(void)) {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            print();
            if (idx < this->data_len - 1)    printf(", ");
        }
        printf(" ]");
    }

    void print() {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            std::cout << *(this->data[idx]);
            if (idx < this->data_len - 1)    printf(", ");
        }
        printf(" ]");
    }

    friend std::ostream &operator<<(std::ostream &output, const vector_pro<T>& target) { 
        output << "[ ";
        for (int64_t idx = 0; idx < target.size(); idx++) {
            output << target[idx];
            if (idx < target.size() - 1)    output << ", ";
        }
        output << " ]";
        return output;            
    }
    
    void merge(const vector_pro<T> &another) {
        // TODO
    }

    iterator_pro<T> begin() {
        return iterator_pro<T>(this->data);
    }

    iterator_pro<T> end() {
        return iterator_pro<T>(this->data, this->data_len);
    }
};

# endif