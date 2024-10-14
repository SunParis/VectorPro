# pragma once

# include <limits>
# include <iostream>
# include <vector>

# include "vector_pro_exception.hpp"
# include "vector_pro_iter.hpp"

# ifndef __LEN_TYPE
    # define __LEN_TYPE 1
    # if __SIZEOF_POINTER__ == 4
        typedef int32_t LEN_TYPE;
    # elif __SIZEOF_POINTER__ == 8
        typedef int64_t LEN_TYPE;
    # else
        typedef long int LEN_TYPE;
    # endif
# endif

# ifndef VECTOR_PRO_DEFAULT_SIZE
    # define VECTOR_PRO_DEFAULT_SIZE 64
# endif


# ifndef VECTOR_PRO

# define VECTOR_PRO 1

template <typename T>
class vector_pro {
protected:
    LEN_TYPE curr_size = 0;
    LEN_TYPE data_len = 0;
    T **_data = null;
    
    void insertionSort(LEN_TYPE left, LEN_TYPE right, int(compare2)(const T &, const T &)) {
        T **arr = this->_data;
        for (LEN_TYPE i = left + 1; i <= right; i++) {
            T *temp = arr[i];
            LEN_TYPE j = i - 1;
            while (j >= left && compare2(*(this->_data[j]), *temp) > 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    void mergesort(LEN_TYPE l, LEN_TYPE m, LEN_TYPE r, int(compare2)(const T &, const T &)) {
        T **arr = this->_data;
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
        this->_data = new T* [ini_size];
        if (this->_data == null) {
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
        this->_data = new T* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.size();
        LEN_TYPE idx = 0;
        for (auto iter = another.begin(); iter != another.end(); iter++) {
            this->_data[idx] = new T(*iter);
            idx++;
        }
    }

    vector_pro(const vector_pro<T> &another) {
        LEN_TYPE ini_size = another.capacity();
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
            return;
        }
        this->_data = new T* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.data_len;
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            this->_data[idx] = new T(another.read_only(idx));
        }
    }

    vector_pro(const T *arr, const LEN_TYPE len) {
        if (arr == null)    throw vector_pro_exception("Target array can't be null.");
        LEN_TYPE ini_size = std::max<LEN_TYPE>(VECTOR_PRO_DEFAULT_SIZE, len);
        
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
            return;
        }
        this->_data = new T* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = len;
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            this->_data[idx] = new T(arr[idx]);
        }
    }

    vector_pro(const LEN_TYPE len, const T& arr) {
        LEN_TYPE ini_size = std::max<LEN_TYPE>(VECTOR_PRO_DEFAULT_SIZE, len);
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
            return;
        }
        this->_data = new T* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = len;
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            this->_data[idx] = new T(arr);
        }
    }
    
    ~vector_pro() {
        if (this->_data != null) {
            if (this->data_len > 0) {
                for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
                    delete this->_data[idx];
                }
                this->data_len = 0;
            }
            delete [] this->_data;
            this->_data = null;
            this->curr_size = 0;
        }
    }
    
    // Capacity
    
    LEN_TYPE size() const noexcept {
        return this->data_len;
    }
    
    size_t max_size() const noexcept {
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
                delete this->_data[idx];
            }
            this->data_len = re_size;
        }
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->_data[idx];
        }
        delete [] this->_data;
        this->_data = tmp;
        this->curr_size = re_size;
        return;
    }
    
    LEN_TYPE capacity() const noexcept {
        return this->curr_size;
    }

    bool empty() const noexcept {
        if (this->data_len == 0) return true;
        return false;
    }

    bool not_empty() const noexcept {
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
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->_data[idx];
        }
        delete [] this->_data;
        this->_data = tmp;
        this->curr_size = re_size;
        return;
    }
    
    void shrink_to_fit() {
        this->resize(this->data_len);
    }

    // Element access

    T& operator[](LEN_TYPE idx) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->data_len) throw vector_pro_exception("Out of range.");
        if (idx < 0) throw vector_pro_exception("Out of range.");
        
        return *(this->_data[idx]);
    }
    
    T& at(const LEN_TYPE idx) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->data_len) throw vector_pro_exception("Out of range.");
        if (idx < 0) throw vector_pro_exception("Out of range.");

        return *(this->_data[idx]);
    }

    T *data() {
        throw vector_pro_exception("Vector_pro doesn't support this operation yet. (Maybet in the near future ?)");
        return null;
    }

    T& front() {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        return *(this->_data[0]);
    }

    T& back() {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        return *(this->_data[this->data_len - 1]);
    }
    
    const T& read_only(LEN_TYPE idx) const {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx >= this->data_len) throw vector_pro_exception("Out of range.");
        if (idx < 0) throw vector_pro_exception("Out of range.");
        return *(this->_data[idx]);
    }
    
    // Modifiers
    
    void assign(LEN_TYPE num, T& target) {
        for (LEN_TYPE idx = 0; idx < num; idx++) {
            if (idx < this->data_len) {
                *this->_data[idx] = T(target);
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
                *this->_data[idx] = T(*iter);
            }
            else {
                this->push(*iter);
            }
            idx++;
            if (iter == include_to) break;
        }
    }

    void push_back(const T& target) {        
        this->push(target);
    }

    void push(const T& target) {
        if (this->data_len == this->curr_size) {
            this->resize(this->curr_size * 2);
        }
        T *tmp = new T(target);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing was done.");
        }        
        this->_data[this->data_len] = tmp;
        this->data_len += 1;
    }
    
    void pop_back() {
        if (this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        this->data_len--;
        delete this->_data[this->data_len];
    }
    
    T pop() {
        if (this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        T ret = T(*this->_data[this->data_len]);
        delete [] this->_data[this->data_len];
        this->data_len -= 1;
        return ret;
    }
            
    // Insert methods
    
    LEN_TYPE insert(LEN_TYPE position, const T& target) {
        if (position > this->data_len)  throw vector_pro_exception("Out of range");
        if (position < 0)  throw vector_pro_exception("Out of range");
        
        if (this->data_len == this->curr_size) {
            this->resize(this->curr_size * 2);
        }
        T *tmp = new T(target);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
        }

        for (LEN_TYPE i = this->data_len; i > position; i--) {
            this->_data[i] = this->_data[i - 1];
        }
        this->_data[position] = tmp;
        this->data_len += 1;
        return position;
    }

    iterator_pro<T> insert(const_iterator_pro<T> position, const T& target) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range");
        
        if (this->data_len == this->curr_size) {
            this->resize(this->curr_size * 2);
        }
        T *tmp = new T(target);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
        }

        LEN_TYPE idx = position.get_idx();
        for (LEN_TYPE i = this->data_len; i > idx; i--) {
            this->_data[i] = this->_data[i - 1];
        }
        this->_data[idx] = tmp;
        this->data_len += 1;
        return iterator_pro(this->_data, idx);
    }
    
    iterator_pro<T> insert(const_iterator_pro<T> position, const_iterator_pro<T> from, const_iterator_pro<T> exclude_to) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Position iterator not of this vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range.");

        LEN_TYPE n = exclude_to.get_idx() - from.get_idx();
        LEN_TYPE idx = position.get_idx();
        if (n <= 0)  throw vector_pro_exception("Number of insert target should be gt 0.");

        if (this->data_len + n >= this->curr_size) {
            this->resize(std::max(this->curr_size * 2, this->data_len + n));
        }

        for (LEN_TYPE i = this->data_len + n - 1; i >= idx + n; i--) {
            this->_data[i] = this->_data[i - n];
        }
        
        LEN_TYPE curr = idx;
        for (auto iter = from; iter != exclude_to; iter++) {
            this->_data[curr] = new T(*iter);
            if (this->_data[curr] == null) {
                throw vector_pro_exception("Out of memory.");
            }
            curr++;
        }        

        this->data_len += n;
        return iterator_pro(this->_data, idx);
    }

    LEN_TYPE emplace(LEN_TYPE position, const T& target) {
        if (position > this->data_len)    throw vector_pro_exception("Out of range.");
        if (position < 0)    throw vector_pro_exception("Out of range.");
        if (position == this->data_len) {
            this->push(target);
            return position;
        }
        else {
            this->insert(position, target);
            return position;
        }
    }

    iterator_pro<T> emplace(const_iterator_pro<T> position, const T& target) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)    throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)    throw vector_pro_exception("Out of range.");
        if (position.get_idx() == this->data_len) {
            this->push(target);
            return (this->end() - 1);
        }
        else {
            this->insert(position.get_idx(), target);
            return iterator_pro<T>(this->_data, position.get_idx());
        }
    }

    void emplace_back(const T& target) {
        this->push(target);
    }

    // Erase methods
    
    LEN_TYPE erase(LEN_TYPE position) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (position >= this->data_len) throw vector_pro_exception("Out of range.");
        if (position < 0) throw vector_pro_exception("Out of range.");
        
        delete this->_data[position];
        this->end -= 1;
        for (LEN_TYPE i = position; i < this->end; i++) {
            this->_data[i] = this->_data[i + 1];
        }
        return position;
    }

    LEN_TYPE erase(LEN_TYPE from, LEN_TYPE include_to) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (from >= this->data_len || include_to >= this->data_len) throw vector_pro_exception("Out of range.");
        if (from < 0 || include_to < 0) throw vector_pro_exception("Out of range.");
        if (from >= include_to) throw vector_pro_exception("Out of range.");
        
        for (LEN_TYPE i = from; i < this->end; i++) {
            if (i <= include_to) {
                delete this->_data[i];
            }
            this->_data[i] = this->_data[include_to - from + 1 + i];
        }
        return from;
    }

    iterator_pro<T> erase(const_iterator_pro<T> position) {        
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (position.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() >= this->data_len) throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0) throw vector_pro_exception("Out of range.");
        
        LEN_TYPE idx = position.get_idx();
        delete this->_data[idx];
        this->end -= 1;
        for (LEN_TYPE i = idx; i < this->end; i++) {
            this->_data[i] = this->_data[i + 1];
        }
        return iterator_pro<T>(this->_data, idx);
    }

    iterator_pro<T> erase(const_iterator_pro<T> from, const_iterator_pro<T> include_to) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (from.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (include_to.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (from.get_idx() >= this->data_len || include_to.get_idx() >= this->data_len) throw vector_pro_exception("Out of range.");
        if (from.get_idx() < 0 || include_to.get_idx() < 0) throw vector_pro_exception("Out of range.");
        if (from.get_idx() > include_to.get_idx()) throw vector_pro_exception("Out of range.");
                
        LEN_TYPE from_idx = from.get_idx();
        LEN_TYPE to_idx = include_to.get_idx();
        if (from_idx > to_idx) {
            LEN_TYPE tmp = from_idx;
            from_idx = to_idx;
            to_idx = tmp;
        }
        for (LEN_TYPE i = from_idx; i < this->end; i++) {
            if (i <= to_idx) {
                delete this->_data[i];
            }
            this->_data[i] = this->_data[to_idx - from_idx + i + 1];
        }
        return iterator_pro<T>(this->_data, from_idx);
    }
        
    void swap(const LEN_TYPE idx1, const LEN_TYPE idx2) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        if (idx1 >= this->data_len || idx2 >= this->data_len) throw vector_pro_exception("Out of range.");
        if (idx1 < 0 || idx2 < 0) throw vector_pro_exception("Out of range.");
        if (idx1 == idx2)   return;
        T *tmp = this->_data[idx1];
        this->_data[idx1] = this->_data[idx2];
        this->_data[idx2] = tmp;
    }

    void swap(vector_pro<T> &another) {
        std::swap(this->_data, another.data);
        std::swap(this->data_len, another.data_len);
        std::swap(this->curr_size, another.curr_size);
    }

    void reverse() {
        LEN_TYPE head = 0, last = this->data_len - 1;
        while (head < last) {
            T *tmp = this->_data[head];
            this->_data[head] = this->_data[last];
            this->_data[last] = tmp;
            head++;
            last--;
        }
    }
    
    void merge(const vector_pro<T> &another) {
        for (auto iter = another.begin(); iter != another.end(); iter++) {
            this->push(*iter);
        }
    }

    void clear() noexcept {
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            delete this->_data[idx];
        }
        this->data_len = 0;
    }

    // Built-in find method
    
    LEN_TYPE find(const T& target, int(compare2)(const T &, const T &), LEN_TYPE from = 0, LEN_TYPE include_to = -1) const {
        if (this->data_len <= 0) return -1;

        if (include_to == -1) include_to = this->data_len - 1;
        if (from == -1) include_to = this->data_len - 1;
        
        if (include_to < from) {
            if (from >= this->data_len)   throw vector_pro_exception("Out of range.");
            for (LEN_TYPE idx = include_to; idx <= from; idx--) {
                if (compare2(*(this->_data[idx]), target) == 0)  return idx;
            }
        }
        else {
            if (include_to >= this->data_len)   throw vector_pro_exception("Out of range.");
            for (LEN_TYPE idx = from; idx <= include_to; idx--) {
                if (compare2(*(this->_data[idx]), target) == 0)  return idx;
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
            if (from >= this->data_len)   throw vector_pro_exception("Out of range.");
            for (LEN_TYPE idx = include_to; idx <= from; idx--) {
                if (compare2(*(this->_data[idx]), target) == 0)  return idx;
            }
        }
        else {
            if (include_to >= this->data_len)   throw vector_pro_exception("Out of range.");
            for (LEN_TYPE idx = from; idx <= include_to; idx--) {
                if (compare2(*(this->_data[idx]), target) == 0)  return idx;
            }
        }

        return -1;
    }
    
    // Built-in tim sort
    
    void sort(int(compare2)(const T &, const T &)) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
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
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        
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
    
    // Print methods
    
    void print(void(print)(T&)) const {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            print(*(this->_data[idx]));
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
            std::cout << *(this->_data[idx]);
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
    
    void operator= (const vector_pro<T>& another) {
        this->clear();
        delete this->_data;
        LEN_TYPE ini_size = another.capacity();
        if (ini_size <= 0) {
            throw vector_pro_exception("Initial size of vector should gt 0.");
            return;
        }
        this->_data = new T* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory, nothing done.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.data_len;
        for (LEN_TYPE idx = 0; idx < this->data_len; idx++) {
            this->_data[idx] = new T(another.read_only(idx));
        }
    }

    // Iterators
    
    iterator_pro<T> begin() noexcept {
        return iterator_pro<T>(this->_data);
    }

    iterator_pro<T> end() noexcept {
        return iterator_pro<T>(this->_data, this->data_len);
    }

    iterator_pro<T> rbegin() noexcept {
        return iterator_pro<T>(this->_data, this->data_len - 1, true);
    }

    iterator_pro<T> rend() noexcept {
        return iterator_pro<T>(this->_data, -1, true);
    }

    const_iterator_pro<T> cbegin() const noexcept {
        return const_iterator_pro<T>(this->_data);
    }

    const_iterator_pro<T> cend() const noexcept {
        return const_iterator_pro<T>(this->_data, this->data_len);
    }

    const_iterator_pro<T> crbegin() const noexcept {
        return const_iterator_pro<T>(this->_data, this->data_len - 1, true);
    }

    const_iterator_pro<T> crend() const noexcept {
        return const_iterator_pro<T>(this->_data, -1, true);
    }
};

# endif