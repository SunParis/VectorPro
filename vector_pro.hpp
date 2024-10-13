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

# if __SIZEOF_POINTER__ == 4
    typedef int32_t LEN_TYPE;
# elif __SIZEOF_POINTER__ == 8
    typedef int64_t LEN_TYPE;
# else
    typedef long int LEN_TYPE;
# endif

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
    LEN_TYPE curr_pos = 0;
public:
    
    iterator_pro() {
        // Do Nothing
    }

    iterator_pro(T **source, LEN_TYPE idx = 0) {
        this->data = source;
        this->curr_pos = idx;
    }
    
    LEN_TYPE get_idx() const {
        return this->curr_pos;
    }

    T** const get_data() const {
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

    iterator_pro operator+(const int step) {
        iterator_pro<T> ret(this->data, this->curr_pos + step);
        return ret;
    }

    iterator_pro operator-(const int step) {
        iterator_pro<T> ret(this->data, this->curr_pos - step);
        return ret;
    }

    bool operator==(const iterator_pro<T>& another) const {
        return ((this->data == another.get_data()) && (this->curr_pos == another.get_idx()));
    }

    bool operator!=(const iterator_pro<T>& another) const {
        return ((this->data != another.get_data()) || (this->curr_pos != another.get_idx()));
    }

    T& operator*() {
        return *(this->data[curr_pos]);
    }
};

template <typename T>
class vector_pro {
protected:
    LEN_TYPE curr_size = 0;
    LEN_TYPE data_len = 0;
    T **data = null;
    
    void insertionSort(LEN_TYPE left, LEN_TYPE right, int(compare2)(const T &, const T &)) {
        T **arr = this->data;
        for (LEN_TYPE i = left + 1; i <= right; i++) {
            T *temp = arr[i];
            LEN_TYPE j = i - 1;
            while (j >= left && compare2(*(this->data[j]), *temp) > 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    void mergesort(LEN_TYPE l, LEN_TYPE m, LEN_TYPE r, int(compare2)(const T &, const T &)) {
        T **arr = this->data;
        LEN_TYPE len1 = m - l + 1, len2 = r - m;
        T **left = new T*[len1];
        T **right = new T*[len2];
    
        for (LEN_TYPE i = 0; i < len1; i++)
            left[i] = arr[l + i];
        for (LEN_TYPE i = 0; i < len2; i++)
            right[i] = arr[m + 1 + i];

        LEN_TYPE i = 0, j = 0, k = l;
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
        LEN_TYPE ini_size = VECTOR_PRO_DEFAULT_SIZE;
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
    
    vector_pro(const std::vector<T> &another) {
        LEN_TYPE ini_size = another.capacity();
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
        this->data_len = another.size();
        LEN_TYPE idx = 0;
        for (auto iter = another.begin(); iter != another.end(); iter++) {
            this->data[idx] = new T(*iter);
            idx++;
        }
    }

    vector_pro(const vector_pro<T> &another) {
        LEN_TYPE ini_size = another.capacity();
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
        this->data_len = another.data_len;
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            this->data[idx] = new T(another.read_only(idx));
        }
    }

    vector_pro(const T *arr, const LEN_TYPE len) {
        if (arr == null)    throw vector_pro_exception("Target array can't be null.");
        LEN_TYPE ini_size = std::max<LEN_TYPE>(VECTOR_PRO_DEFAULT_SIZE, len);
        
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
        this->data_len = len;
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            this->data[idx] = new T(arr[idx]);
        }
    }

    vector_pro(const LEN_TYPE len, const T& arr) {
        LEN_TYPE ini_size = std::max<LEN_TYPE>(VECTOR_PRO_DEFAULT_SIZE, len);
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
        this->data_len = len;
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            this->data[idx] = new T(arr);
        }
    }
    
    ~vector_pro() {
        if (this->data != null) {
            if (this->data_len > 0) {
                for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
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
    
    LEN_TYPE size() const {
        return this->data_len;
    }
    
    size_t max_size() const {
        return std::numeric_limits<LEN_TYPE>::max();
    }
    
    void resize(const LEN_TYPE re_size) {
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
            for (LEN_TYPE idx = re_size; idx < this->data_len; idx++) {
                delete this->data[idx];
            }
            this->data_len = re_size;
        }
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->data[idx];
        }
        delete [] this->data;
        this->data = tmp;
        this->curr_size = re_size;
        return;
    }
    
    LEN_TYPE capacity() const {
        return this->curr_size;
    }

    bool empty() const {
        if (this->data_len == 0) return true;
        return false;
    }

    bool not_empty() const {
        return !(this->empty());
    }
    
    void reserve(const LEN_TYPE re_size) {
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
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->data[idx];
        }
        delete [] this->data;
        this->data = tmp;
        this->curr_size = re_size;
        return;
    }
    
    void shrink_to_fit() {
        this->resize(this->data_len);
    }

    // Element access

    T& operator[](LEN_TYPE idx) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->data_len) throw vector_pro_exception("Illegal index.");
        return *(this->data[idx]);
    }
    
    T& at(const LEN_TYPE idx) {
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

    const T& read_only(LEN_TYPE idx) const {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->data_len) throw vector_pro_exception("Illegal index.");
        return *(this->data[idx]);
    }
    
    // Modifiers
    
    void assign(LEN_TYPE num, T& target) {
        for (LEN_TYPE idx = 0; idx < num; idx++) {
            if (idx < this->data_len) {
                *this->data[idx] = T(target);
            }
            else {
                this->push(target);
            }
        }
    }

    void assign(iterator_pro<T> from, iterator_pro<T> include_to) {
        LEN_TYPE idx = 0;
        for (auto iter = from; ; iter++) {
            if (idx < this->data_len) {
                *this->data[idx] = T(*iter);
            }
            else {
                this->push(*iter);
            }
            idx++;
            if (iter == include_to) break;
        }
    }

    LEN_TYPE push_back(const T& target) {
        
        return this->push(target);
    }

    LEN_TYPE push(const T& target) {
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
            
    void insert(LEN_TYPE idx, const T& target) {
        // TODO

    }

    void insert(LEN_TYPE idx, LEN_TYPE n, const T& target) {
        // TODO
    }

    void insert(LEN_TYPE idx, iterator_pro<T> from, iterator_pro<T> include_to) {
        // TODO
    }

    void erase(LEN_TYPE target) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (target >= this->data_len) throw vector_pro_exception("Illegal index.");
        if (target < 0) throw vector_pro_exception("Illegal index.");
        
        delete this->data[target];
        this->end -= 1;
        for (LEN_TYPE i = target; i < this->end; i++) {
            this->data[i] = this->data[i + 1];
        }
    }

    void erase(LEN_TYPE from, LEN_TYPE include_to) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (from >= this->data_len || include_to >= this->data_len) throw vector_pro_exception("Illegal index.");
        if (from < 0 || include_to < 0) throw vector_pro_exception("Illegal index.");
        if (from >= include_to) throw vector_pro_exception("Illegal index.");
        
        for (LEN_TYPE i = from; i < this->end; i++) {
            if (i <= include_to) {
                delete this->data[i];
            }
            this->data[i] = this->data[include_to - from + 1 + i];
        }
    }

    void erase(iterator_pro<T> target) {        
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (target.get_data() != this->data)   throw vector_pro_exception("Iterator not of this vector.");
        if (target.get_idx() >= this->data_len) throw vector_pro_exception("Illegal index.");
        if (target.get_idx() < 0) throw vector_pro_exception("Illegal index.");
        
        LEN_TYPE idx = target.get_idx();
        delete this->data[idx];
        this->end -= 1;
        for (LEN_TYPE i = idx; i < this->end; i++) {
            this->data[i] = this->data[i + 1];
        }
    }

    void erase(iterator_pro<T> from, iterator_pro<T> include_to) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (from.get_data() != this->data)   throw vector_pro_exception("Iterator not of this vector.");
        if (include_to.get_data() != this->data)   throw vector_pro_exception("Iterator not of this vector.");
        if (from.get_idx() >= this->data_len || include_to.get_idx() >= this->data_len) throw vector_pro_exception("Illegal index.");
        if (from.get_idx() < 0 || include_to.get_idx() < 0) throw vector_pro_exception("Illegal index.");
        if (from.get_idx() > include_to.get_idx()) throw vector_pro_exception("Illegal index.");
                
        LEN_TYPE from_idx = from.get_idx();
        LEN_TYPE to_idx = include_to.get_idx();
        for (LEN_TYPE i = from_idx; i < this->end; i++) {
            if (i <= to_idx) {
                delete this->data[i];
            }
            this->data[i] = this->data[to_idx - from_idx + i + 1];
        }
    }
        
    void swap(const LEN_TYPE idx1, const LEN_TYPE idx2) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx1 >= this->data_len || idx2 >= this->data_len) throw vector_pro_exception("Illegal index.");
        if (idx1 < 0 || idx2 < 0) throw vector_pro_exception("Illegal index.");
        if (idx1 == idx2)   return;
        T *tmp = this->data[idx1];
        this->data[idx1] = this->data[idx2];
        this->data[idx2] = tmp;
    }

    void swap(vector_pro<T> &another) {
        std::swap(this->data, another.data);
        std::swap(this->data_len, another.data_len);
        std::swap(this->curr_size, another.curr_size);
    }
    
    void clear() {
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            delete this->data[idx];
        }
        this->data_len = 0;
    }

    LEN_TYPE find(const T& target, int(compare2)(const T &, const T &), LEN_TYPE from = 0, LEN_TYPE include_to = -1) const {
        if (this->data_len <= 0) return -1;

        if (include_to == -1) include_to = this->data_len - 1;
        if (from == -1) include_to = this->data_len - 1;
        
        if (include_to < from) {
            if (from >= this->data_len)   throw vector_pro_exception("Illegal index.");
            for (LEN_TYPE idx = include_to; idx <= from; idx--) {
                if (compare2(*(this->data[idx]), target) == 0)  return idx;
            }
        }
        else {
            if (include_to >= this->data_len)   throw vector_pro_exception("Illegal index.");
            for (LEN_TYPE idx = from; idx <= include_to; idx--) {
                if (compare2(*(this->data[idx]), target) == 0)  return idx;
            }
        }

        return -1;
    }

    LEN_TYPE find(const T& target, LEN_TYPE from = 0, LEN_TYPE include_to = -1) const {
        if (this->data_len <= 0) return -1;

        auto lambda = [](const T & a, const T & b) -> int {
            if (a == b) return 1;
            return 0;
        };
        int (*same2)(const T &, const T &) = lambda;
        
        if (include_to == -1) include_to = this->data_len - 1;
        if (from == -1) include_to = this->data_len - 1;
        
        if (include_to < from) {
            if (from >= this->data_len)   throw vector_pro_exception("Illegal index.");
            for (LEN_TYPE idx = include_to; idx <= from; idx--) {
                if (compare2(*(this->data[idx]), target) == 0)  return idx;
            }
        }
        else {
            if (include_to >= this->data_len)   throw vector_pro_exception("Illegal index.");
            for (LEN_TYPE idx = from; idx <= include_to; idx--) {
                if (compare2(*(this->data[idx]), target) == 0)  return idx;
            }
        }

        return -1;
    }
    
    void sort(int(compare2)(const T &, const T &)) {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        const int RUN = 32;
        LEN_TYPE n = this->size();
        for (LEN_TYPE i = 0; i < n; i += RUN)
            insertionSort(i, (i + 31 < n - 1) ? (i + 31) : (n - 1), compare2);

        for (LEN_TYPE size = RUN; size < n; size = 2 * size) {
            for (LEN_TYPE left = 0; left < n; left += 2 * size) {
                LEN_TYPE mid = left + size - 1;
                LEN_TYPE right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

                if (mid < right)
                    mergesort(left, mid, right, compare2);
            }
        }
    }

    void sort() {
        if (this->data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        
        auto lambda = [](const T & a, const T & b) -> int {
            if (a > b)  return 1;
            else if (a < b) return -1;
            return 0;
        };
        int (*compare2)(const T &, const T &) = lambda;
        
        const int RUN = 32;
        LEN_TYPE n = this->size();
        for (LEN_TYPE i = 0; i < n; i += RUN)
            insertionSort(i, (i + 31 < n - 1) ? (i + 31) : (n - 1), compare2);

        for (LEN_TYPE size = RUN; size < n; size = 2 * size) {
            for (LEN_TYPE left = 0; left < n; left += 2 * size) {
                LEN_TYPE mid = left + size - 1;
                LEN_TYPE right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

                if (mid < right)
                    mergesort(left, mid, right, compare2);
            }
        }
    }
    
    void print(void(print)(T&)) const {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            print(*(this->data[idx]));
            if (idx < this->data_len - 1)    printf(", ");
        }
        printf(" ]");
    }

    void print(void(print)(void)) const {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            print();
            if (idx < this->data_len - 1)    printf(", ");
        }
        printf(" ]");
    }

    void print() const {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            std::cout << *(this->data[idx]);
            if (idx < this->data_len - 1)    printf(", ");
        }
        printf(" ]");
    }

    friend std::ostream& operator<<(std::ostream &output, const vector_pro<T>& target) { 
        output << "[ ";
        for (LEN_TYPE idx = 0; idx < target.size(); idx++) {
            output << target.read_only(idx);
            if (idx < target.size() - 1)    output << ", ";
        }
        if (target.size() == 0) output << "null";
        output << " ]";
        return output;            
    }
    
    void merge(const vector_pro<T> &another) {
        for (auto iter = another.begin(); iter != another.end(); iter++) {
            this->push(*iter);
        }
    }

    iterator_pro<T> begin() {
        return iterator_pro<T>(this->data);
    }

    iterator_pro<T> end() {
        return iterator_pro<T>(this->data, this->data_len);
    }
};

# endif