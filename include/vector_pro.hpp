# pragma once

# include <limits>
# include <iostream>
# include <vector>
# include <initializer_list>

# ifndef ___SIZE_TYPE___
    # define ___SIZE_TYPE___ 1
    # if __SIZEOF_POINTER__ == 4
        typedef int32_t size_type;
    # elif __SIZEOF_POINTER__ == 8
        typedef int64_t size_type;
    # else
        typedef long int size_type;
    # endif
# endif

# ifndef VECTOR_PRO_DEFAULT_SIZE
    # define VECTOR_PRO_DEFAULT_SIZE 64
# endif

# include "vector_pro_exception.hpp"
# include "vector_pro_iter.hpp"

# ifndef __VECTOR_PRO__

# define __VECTOR_PRO__ 1

# define _DOUBLE_(x) (x == 0 ? 1 : (2 * (std::size_t)x))

template <class value_type>
class vector_pro {
protected:
    size_type curr_size = 0;
    size_type data_len = 0;
    value_type **_data = null;
    
    void insertionSort(size_type left, size_type right, int(compare2)(const value_type &, const value_type &)) {
        value_type **arr = this->_data;
        for (size_type i = left + 1; i <= right; i++) {
            value_type *temp = arr[i];
            size_type j = i - 1;
            while (j >= left && compare2(*(this->_data[j]), *temp) > 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    void mergesort(size_type l, size_type m, size_type r, int(compare2)(const value_type &, const value_type &)) {
        value_type **arr = this->_data;
        size_type len1 = m - l + 1, len2 = r - m;
        value_type **left = new value_type*[len1];
        value_type **right = new value_type*[len2];
    
        for (size_type i = 0; i < len1; i++)
            left[i] = arr[l + i];
        for (size_type i = 0; i < len2; i++)
            right[i] = arr[m + 1 + i];

        size_type i = 0, j = 0, k = l;
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
        size_type ini_size = VECTOR_PRO_DEFAULT_SIZE;
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = 0;
    }
            
    vector_pro(const std::vector<value_type>& another) {
        size_type ini_size = std::max<size_type>(VECTOR_PRO_DEFAULT_SIZE, another.capacity());
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.size();
        size_type idx = 0;
        for (auto iter = another.begin(); iter != another.end(); iter++) {
            this->_data[idx] = new value_type(*iter);
            idx++;
        }
    }

    vector_pro(const std::initializer_list<value_type>& another) {
        size_type ini_size = std::max<size_type>(VECTOR_PRO_DEFAULT_SIZE, another.size());
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.size();
        size_type idx = 0;
        for (auto iter = another.begin(); iter != another.end(); iter++) {
            this->_data[idx] = new value_type(*iter);
            idx++;
        }
    }

    vector_pro(const vector_pro<value_type>& another) {
        size_type ini_size = std::max<size_type>(VECTOR_PRO_DEFAULT_SIZE, another.capacity());
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.data_len;

        size_type idx = 0;
        for (auto citer = another.cbegin(); citer != another.cend(); citer++) {
            this->_data[idx] = new value_type(*citer);
            idx++;
        }
    }

    vector_pro(vector_pro<value_type>&& another) {
        this->destroy();
        std::swap(this->_data, another._data);
        std::swap(this->data_len, another.data_len);
        std::swap(this->curr_size, another.curr_size);
    }

    vector_pro(const value_type *arr, const size_type len) {
        if (arr == null)    throw vector_pro_exception("Target array can't be null.");
        size_type ini_size = std::max<size_type>(VECTOR_PRO_DEFAULT_SIZE, len);
        
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = len;
        for (size_type idx = 0; idx < this->data_len; idx++) {
            this->_data[idx] = new value_type(arr[idx]);
        }
    }

    vector_pro(const size_type len) {
        size_type ini_size = std::max<size_type>(VECTOR_PRO_DEFAULT_SIZE, len);;
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = 0;
    }
    
    vector_pro(const size_type len, const value_type& val) {
        size_type ini_size = std::max<size_type>(VECTOR_PRO_DEFAULT_SIZE, len);
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = len;
        for (size_type idx = 0; idx < this->data_len; idx++) {
            this->_data[idx] = new value_type(val);
        }
    }

    vector_pro(const_iterator_pro<value_type>from, const_iterator_pro<value_type>exclude_to) {
        if (from.get_data() != exclude_to.get_data())  throw vector_pro_exception("Iterator not of same vector.");
        size_type input_len = std::max<size_type>(exclude_to.get_idx() - from.get_idx(), from.get_idx() - exclude_to.get_idx());
        size_type ini_size = std::max<size_type>(VECTOR_PRO_DEFAULT_SIZE, input_len);
        
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->destroy();
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = input_len;
        size_type idx = 0;
        for (auto iter = from; iter != exclude_to; iter++) {
            this->_data[idx] = new value_type(*iter);
            idx++;
        }
    }
    
    ~vector_pro() {
        this->destroy();
    }
    
    // Capacity
    
    size_type size() const noexcept {
        return this->data_len;
    }
    
    size_t max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }
    
    void resize(const size_type re_size) {
        if (re_size < 0) {
            throw vector_pro_exception("Re_size val of vector should be geq 0.");
            return;
        }
        if (re_size == this->curr_size) return;
        value_type **tmp = new value_type*[re_size];
        if (tmp == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        if (re_size < this->curr_size) {
            for (size_type idx = re_size; idx < this->data_len; idx++) {
                delete this->_data[idx];
            }
            this->data_len = re_size;
        }
        for (size_type idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->_data[idx];
        }
        delete [] this->_data;
        this->_data = tmp;
        this->curr_size = re_size;
        return;
    }

    void resize(const size_type re_size, const value_type& val) {
        if (re_size < 0) {
            throw vector_pro_exception("Re_size val of vector should be geq 0.");
            return;
        }
        if (re_size == this->curr_size) return;
        value_type **tmp = new value_type*[re_size];
        if (tmp == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        if (re_size < this->curr_size) {
            for (size_type idx = re_size; idx < this->data_len; idx++) {
                delete this->_data[idx];
            }
            this->data_len = re_size;
        }
        for (size_type idx = 0; idx < this->data_len; idx++) {
            tmp[idx] = this->_data[idx];
        }
        delete [] this->_data;
        for (size_type idx = this->data_len; idx < re_size; idx++) {
            tmp[idx] = new value_type(val);
            if (tmp[idx] == null) {
                throw vector_pro_exception("Out of memory.");
                return;
            }
            this->data_len++;
        }
        this->_data = tmp;
        this->curr_size = re_size;
        return;
    }
    
    size_type capacity() const noexcept {
        return this->curr_size;
    }

    bool empty() const noexcept {
        if (this->data_len == 0) return true;
        return false;
    }

    bool not_empty() const noexcept {
        return !(this->empty());
    }
    
    void reserve(const size_type re_size) {
        if (re_size < 0) {
            throw vector_pro_exception("Re_size val of vector should be geq 0.");
            return;
        }
        if (re_size < this->curr_size) return;
        value_type **tmp = new value_type*[re_size];
        if (tmp == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        for (size_type idx = 0; idx < this->data_len; idx++) {
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

    value_type& operator[](size_type position) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Out of range.");
        if (position >= this->data_len) throw vector_pro_exception("Out of range.");
        if (position < 0) throw vector_pro_exception("Out of range.");
        
        return *(this->_data[position]);
    }
    
    value_type& at(const size_type position) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Out of range.");
        if (position >= this->data_len) throw vector_pro_exception("Out of range.");
        if (position < 0) throw vector_pro_exception("Out of range.");

        return *(this->_data[position]);
    }

    value_type *data() const {
        throw vector_pro_exception("Vector_pro doesn't support this operation yet. (Maybe in the near future ?)");
        return null;
    }

    value_type& front() {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        return *(this->_data[0]);
    }

    value_type& back() {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        return *(this->_data[this->data_len - 1]);
    }
        
    // Modifiers
    
    void assign(size_type num, const value_type& val) {
        if (num < 0)   throw vector_pro_exception("Number of insert target should be geq 0.");
        for (size_type idx = 0; idx < num; idx++) {
            if (idx < this->data_len) {
                *this->_data[idx] = value_type(val);
            }
            else {
                this->push(val);
            }
        }
        for (size_type idx = num; idx < this->data_len; idx++) {
            delete this->_data[idx];
        }
        this->data_len = num;
    }

    void assign(iterator_pro<value_type> from, iterator_pro<value_type> exclude_to) {
        size_type idx = 0;
        if (from.get_data() != exclude_to.get_data())   throw vector_pro_exception("Iterator not of same vector.");
        for (auto iter = from; iter != exclude_to; iter++) {
            if (idx < this->data_len) {
                *this->_data[idx] = value_type(*iter);
            }
            else {
                this->push(*iter);
            }
            idx++;
        }
        for (size_type _idx = idx; _idx < this->data_len; _idx++) {
            delete this->_data[_idx];
        }
        this->data_len = idx;
    }

    void assign(std::initializer_list<value_type> another) {
        size_type idx = 0;
        for (auto iter = another.begin(); iter != another.end(); iter++) {
            if (idx < this->data_len) {
                *this->_data[idx] = value_type(*iter);
            }
            else {
                this->push(*iter);
            }
            idx++;
        }
        for (size_type _idx = idx; _idx < this->data_len; _idx++) {
            delete this->_data[_idx];
        }
        this->data_len = idx;
    }

    void push_back(const value_type& val) {        
        this->push(val);
    }

    void push(const value_type& val) {
        if (this->data_len == this->curr_size) {
            this->resize(_DOUBLE_(this->curr_size));
        }
        value_type *tmp = new value_type(val);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory.");
        }        
        this->_data[this->data_len] = tmp;
        this->data_len += 1;
    }
    
    void pop_back() {
        if (this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        this->data_len--;
        delete this->_data[this->data_len];
    }
    
    value_type pop() {
        if (this->data_len <= 0) throw vector_pro_exception("Vector is empty.");
        value_type ret = value_type(*this->_data[this->data_len - 1]);
        delete [] this->_data[this->data_len - 1];
        this->data_len -= 1;
        return ret;
    }
            
    // Insert methods
    
    size_type insert(size_type position, const value_type& val) {
        if (position > this->data_len)  throw vector_pro_exception("Out of range");
        if (position < 0)  throw vector_pro_exception("Out of range");
        
        if (this->data_len == this->curr_size) {
            this->resize(_DOUBLE_(this->curr_size));
        }
        value_type *tmp = new value_type(val);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory.");
        }

        for (size_type i = this->data_len; i > position; i--) {
            this->_data[i] = this->_data[i - 1];
        }
        this->_data[position] = tmp;
        this->data_len += 1;
        return position;
    }

    iterator_pro<value_type> insert(iterator_pro<value_type> position, const value_type& val) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range");
        
        if (this->data_len == this->curr_size) {
            this->resize(_DOUBLE_(this->curr_size));
        }
        value_type *tmp = new value_type(val);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory.");
        }

        size_type idx = position.get_idx();
        for (size_type i = this->data_len; i > idx; i--) {
            this->_data[i] = this->_data[i - 1];
        }
        this->_data[idx] = tmp;
        this->data_len += 1;
        return iterator_pro(this->_data, idx);
    }

    const_iterator_pro<value_type> insert(const_iterator_pro<value_type> position, const value_type& val) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range");
        
        if (this->data_len == this->curr_size) {
            this->resize(_DOUBLE_(this->curr_size));
        }
        value_type *tmp = new value_type(val);
        if (tmp == null) {
            throw vector_pro_exception("Out of memory.");
        }

        size_type idx = position.get_idx();
        for (size_type i = this->data_len; i > idx; i--) {
            this->_data[i] = this->_data[i - 1];
        }
        this->_data[idx] = tmp;
        this->data_len += 1;
        return const_iterator_pro(this->_data, idx);
    }

    iterator_pro<value_type> insert(iterator_pro<value_type> position, size_type num, const value_type& val) {
        if (num == 0)   return iterator_pro(position);
        if (num < 0)  throw vector_pro_exception("Number of insert target should be geq 0.");
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector."); 
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range");
        
        size_type n = num;
        size_type idx = position.get_idx();

        if (this->data_len + n >= this->curr_size) {
            this->resize(std::max<size_type>(_DOUBLE_(this->curr_size), this->data_len + n));
        }

        for (size_type i = this->data_len + n - 1; i >= idx + n; i--) {
            this->_data[i] = this->_data[i - n];
        }
        
        for (size_type curr = idx; curr < n; curr++) {
            this->_data[curr + idx] = new value_type(val);
            if (this->_data[curr + idx] == null) {
                throw vector_pro_exception("Out of memory.");
            }
        }        

        this->data_len += n;
        return iterator_pro(this->_data, idx);
    }

    const_iterator_pro<value_type> insert(const_iterator_pro<value_type> position, size_type num, const value_type& val) {
        if (num == 0)   return const_iterator_pro(position);
        if (num < 0)  throw vector_pro_exception("Number of insert target should be geq 0.");
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector."); 
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range");
        
        size_type n = num;
        size_type idx = position.get_idx();

        if (this->data_len + n >= this->curr_size) {
            this->resize(std::max<size_type>(_DOUBLE_(this->curr_size), this->data_len + n));
        }

        for (size_type i = this->data_len + n - 1; i >= idx + n; i--) {
            this->_data[i] = this->_data[i - n];
        }
        
        for (size_type curr = idx; curr < n; curr++) {
            this->_data[curr + idx] = new value_type(val);
            if (this->_data[curr + idx] == null) {
                throw vector_pro_exception("Out of memory.");
            }
        }        

        this->data_len += n;
        return const_iterator_pro(this->_data, idx);
    }
    
    iterator_pro<value_type> insert(iterator_pro<value_type> position, const_iterator_pro<value_type> from, const_iterator_pro<value_type> exclude_to) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (from.get_data() != exclude_to.get_data())  throw vector_pro_exception("Iterator not of same vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range.");

        size_type n = exclude_to.get_idx() - from.get_idx();
        size_type idx = position.get_idx();
        if (n == 0)   return iterator_pro(position);
        if (n < 0)  throw vector_pro_exception("Number of insert target should be geq 0.");

        if (this->data_len + n >= this->curr_size) {
            this->resize(std::max<size_type>(_DOUBLE_(this->curr_size), this->data_len + n));
        }

        for (size_type i = this->data_len + n - 1; i >= idx + n; i--) {
            this->_data[i] = this->_data[i - n];
        }
        
        size_type curr = idx;
        for (auto iter = from; iter != exclude_to; iter++) {
            this->_data[curr] = new value_type(*iter);
            if (this->_data[curr] == null) {
                throw vector_pro_exception("Out of memory.");
            }
            curr++;
        }        

        this->data_len += n;
        return iterator_pro(this->_data, idx);
    }

    const_iterator_pro<value_type> insert(const_iterator_pro<value_type> position, const_iterator_pro<value_type> from, const_iterator_pro<value_type> exclude_to) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (from.get_data() != exclude_to.get_data())  throw vector_pro_exception("Iterator not of same vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range.");

        size_type n = exclude_to.get_idx() - from.get_idx();
        size_type idx = position.get_idx();
        if (n == 0)   return const_iterator_pro(position);
        if (n < 0)  throw vector_pro_exception("Number of insert target should be geq 0.");

        if (this->data_len + n >= this->curr_size) {
            this->resize(std::max<size_type>(_DOUBLE_(this->curr_size), this->data_len + n));
        }

        for (size_type i = this->data_len + n - 1; i >= idx + n; i--) {
            this->_data[i] = this->_data[i - n];
        }
        
        size_type curr = idx;
        for (auto iter = from; iter != exclude_to; iter++) {
            this->_data[curr] = new value_type(*iter);
            if (this->_data[curr] == null) {
                throw vector_pro_exception("Out of memory.");
            }
            curr++;
        }        

        this->data_len += n;
        return const_iterator_pro(this->_data, idx);
    }

    iterator_pro<value_type> insert(iterator_pro<value_type> position, const std::initializer_list<value_type>& li) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range.");

        size_type n = li.size();
        size_type idx = position.get_idx();
        if (n == 0)   return iterator_pro(position);
        if (n < 0)  throw vector_pro_exception("Number of insert target should be geq 0.");

        if (this->data_len + n >= this->curr_size) {
            this->resize(std::max<size_type>(_DOUBLE_(this->curr_size), this->data_len + n));
        }

        for (size_type i = this->data_len + n - 1; i >= idx + n; i--) {
            this->_data[i] = this->_data[i - n];
        }
        
        size_type curr = idx;
        for (auto iter = li.begin(); iter != li.end(); iter++) {
            this->_data[curr] = new value_type(*iter);
            if (this->_data[curr] == null) {
                throw vector_pro_exception("Out of memory.");
            }
            curr++;
        }        

        this->data_len += n;
        return iterator_pro(this->_data, idx);
    }

    const_iterator_pro<value_type> insert(const_iterator_pro<value_type> position, const std::initializer_list<value_type>& li) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)  throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)  throw vector_pro_exception("Out of range.");

        size_type n = li.size();
        size_type idx = position.get_idx();
        if (n == 0)   return const_iterator_pro(position);
        if (n < 0)  throw vector_pro_exception("Number of insert target should be geq 0.");

        if (this->data_len + n >= this->curr_size) {
            this->resize(std::max<size_type>(_DOUBLE_(this->curr_size), this->data_len + n));
        }

        for (size_type i = this->data_len + n - 1; i >= idx + n; i--) {
            this->_data[i] = this->_data[i - n];
        }
        
        size_type curr = idx;
        for (auto iter = li.begin(); iter != li.end(); iter++) {
            this->_data[curr] = new value_type(*iter);
            if (this->_data[curr] == null) {
                throw vector_pro_exception("Out of memory.");
            }
            curr++;
        }        

        this->data_len += n;
        return const_iterator_pro(this->_data, idx);
    }

    size_type emplace(size_type position, const value_type& val) {
        if (position > this->data_len)    throw vector_pro_exception("Out of range.");
        if (position < 0)    throw vector_pro_exception("Out of range.");
        if (position == this->data_len) {
            this->push(val);
            return position;
        }
        else {
            this->insert(position, val);
            return position;
        }
    }

    const_iterator_pro<value_type> emplace(const_iterator_pro<value_type> position, const value_type& val) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)    throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)    throw vector_pro_exception("Out of range.");
        if (position.get_idx() == this->data_len) {
            this->push(val);
            return (this->cend() - 1);
        }
        else {
            this->insert(position.get_idx(), val);
            return const_iterator_pro<value_type>(this->_data, position.get_idx());
        }
    }

    iterator_pro<value_type> emplace(iterator_pro<value_type> position, const value_type& val) {
        if (position.get_data() != this->_data)  throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() > this->data_len)    throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0)    throw vector_pro_exception("Out of range.");
        if (position.get_idx() == this->data_len) {
            this->push(val);
            return (this->end() - 1);
        }
        else {
            this->insert(position.get_idx(), val);
            return iterator_pro<value_type>(this->_data, position.get_idx());
        }
    }

    void emplace_back(const value_type& val) {
        this->push(val);
    }

    // Erase methods
    
    size_type erase(size_type position) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Out of range.");
        if (position >= this->data_len) throw vector_pro_exception("Out of range.");
        if (position < 0) throw vector_pro_exception("Out of range.");
        
        delete this->_data[position];
        this->data_len -= 1;
        for (size_type i = position; i < this->data_len; i++) {
            this->_data[i] = this->_data[i + 1];
        }
        return position;
    }

    size_type erase(size_type from, size_type exclude_to) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Out of range.");
        if (from >= this->data_len || exclude_to > this->data_len) throw vector_pro_exception("Out of range.");
        if (from < 0 || exclude_to < 0) throw vector_pro_exception("Out of range.");
        if (from >= exclude_to) throw vector_pro_exception("Out of range.");
        
        this->data_len -= (exclude_to - from);
        for (size_type i = from; i < this->data_len; i++) {
            if (i < exclude_to) {
                delete this->_data[i];
            }
            this->_data[i] = this->_data[exclude_to - from + i];
        }
        return from;
    }

    iterator_pro<value_type> erase(const_iterator_pro<value_type> position) {        
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Out of range.");
        if (position.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (position.get_idx() >= this->data_len) throw vector_pro_exception("Out of range.");
        if (position.get_idx() < 0) throw vector_pro_exception("Out of range.");
        
        size_type idx = position.get_idx();
        delete this->_data[idx];
        this->data_len -= 1;
        for (size_type i = idx; i < this->data_len; i++) {
            this->_data[i] = this->_data[i + 1];
        }
        return iterator_pro<value_type>(this->_data, idx);
    }

    iterator_pro<value_type> erase(const_iterator_pro<value_type> from, const_iterator_pro<value_type> exclude_to) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Out of range.");
        if (from.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (exclude_to.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (from.get_idx() >= this->data_len || exclude_to.get_idx() > this->data_len) throw vector_pro_exception("Out of range.");
        if (from.get_idx() < 0 || exclude_to.get_idx() < 0) throw vector_pro_exception("Out of range.");
        if (from.get_idx() > exclude_to.get_idx()) throw vector_pro_exception("Out of range.");
                
        size_type from_idx = from.get_idx();
        size_type to_idx = exclude_to.get_idx();
        this->data_len -= (to_idx - from_idx);
        for (size_type i = from_idx; i < this->data_len; i++) {
            if (i < to_idx) {
                delete this->_data[i];
            }
            this->_data[i] = this->_data[to_idx - from_idx + i];
        }
        return iterator_pro<value_type>(this->_data, from_idx);
    }
        
    void swap(const size_type idx1, const size_type idx2) {
        if (this->_data == null || this->data_len <= 0) throw vector_pro_exception("Out of range.");
        if (idx1 >= this->data_len || idx2 >= this->data_len) throw vector_pro_exception("Out of range.");
        if (idx1 < 0 || idx2 < 0) throw vector_pro_exception("Out of range.");
        if (idx1 == idx2)   return;
        value_type *tmp = this->_data[idx1];
        this->_data[idx1] = this->_data[idx2];
        this->_data[idx2] = tmp;
    }

    void swap(const_iterator_pro<value_type> idx1, const_iterator_pro<value_type> idx2) {
        if (idx1.get_data() != this->_data || idx2.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        std::swap(this->_data[idx1.get_idx()], this->_data[idx2.get_idx()]);
    }

    void swap(vector_pro<value_type> &another) {
        std::swap(this->_data, another._data);
        std::swap(this->data_len, another.data_len);
        std::swap(this->curr_size, another.curr_size);
    }

    void reverse() {
        size_type head = 0, last = this->data_len - 1;
        while (head < last) {
            value_type *tmp = this->_data[head];
            this->_data[head] = this->_data[last];
            this->_data[last] = tmp;
            head++;
            last--;
        }
    }
    
    void merge(const vector_pro<value_type> &another) {
        for (auto iter = another.cbegin(); iter != another.cend(); iter++) {
            this->push(*iter);
        }
    }

    void clear() noexcept {
        for (size_type idx = 0; idx < this->data_len; idx++) {
            delete this->_data[idx];
        }
        this->data_len = 0;
    }

    void destroy() noexcept {
        this->clear();
        this->curr_size = 0;
        if (this->_data != null) {
            delete [] this->_data;
            this->_data = null;
        }
    }
    
    // Built-in find method
    
    size_type find(const value_type& target, int(compare2)(const value_type &, const value_type &), size_type from = 0, size_type exclude_to = -1) const {
        if (this->data_len <= 0) return -1;

        if (exclude_to == -1) exclude_to = this->data_len - 1;
        
        for (size_type iter = from; iter != exclude_to; iter++) {
            if (iter < 0) throw vector_pro_exception("Out of range.");
            if (iter >= this->data_len) throw vector_pro_exception("Out of range.");
            
            if (compare2(*this->_data[iter], target) == 0)   return iter;
        }

        return -1;
    }

    iterator_pro<value_type> find(const value_type& target, int(compare2)(const value_type &, const value_type &), iterator_pro<value_type> from, iterator_pro<value_type> exclude_to) const {
        if (from.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (exclude_to.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (this->data_len <= 0) return iterator_pro<value_type>(this->_data, exclude_to.get_idx());
        
        for (auto iter = from; iter != exclude_to; iter++) {
            if (iter.get_idx() < 0) throw vector_pro_exception("Out of range.");
            if (iter.get_idx() >= this->data_len) throw vector_pro_exception("Out of range.");
            
            if (compare2(*iter, target) == 0)   return iterator_pro<value_type>(this->_data, iter.get_idx());
        }

        return iterator_pro<value_type>(this->_data, exclude_to.get_idx());
    }
    
    const_iterator_pro<value_type> find(const value_type& target, int(compare2)(const value_type &, const value_type &), const_iterator_pro<value_type> from, const_iterator_pro<value_type> exclude_to) const {
        if (from.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (exclude_to.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (this->data_len <= 0) return const_iterator_pro<value_type>(this->_data, exclude_to.get_idx());
        
        for (auto iter = from; iter != exclude_to; iter++) {
            if (iter.get_idx() < 0) throw vector_pro_exception("Out of range.");
            if (iter.get_idx() >= this->data_len) throw vector_pro_exception("Out of range.");
            
            if (compare2(*iter, target) == 0)   return const_iterator_pro<value_type>(this->_data, iter.get_idx());
        }

        return const_iterator_pro<value_type>(this->_data, exclude_to.get_idx());
    }

    size_type find(const value_type& target, size_type from = 0, size_type exclude_to = -1) const {
        if (this->data_len <= 0) return -1;

        if (exclude_to == -1) exclude_to = this->data_len - 1;
        
        for (size_type iter = from; iter != exclude_to; iter++) {
            if (iter < 0) throw vector_pro_exception("Out of range.");
            if (iter >= this->data_len) throw vector_pro_exception("Out of range.");
            
            if (*this->_data[iter] == target)   return iter;
        }

        return -1;
    }

    iterator_pro<value_type> find(const value_type& target, iterator_pro<value_type> from, iterator_pro<value_type> exclude_to) const {
        if (from.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (exclude_to.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (this->data_len <= 0) return iterator_pro<value_type>(this->_data, exclude_to.get_idx());
        
        for (auto iter = from; iter != exclude_to; iter++) {
            if (iter.get_idx() < 0) throw vector_pro_exception("Out of range.");
            if (iter.get_idx() >= this->data_len) throw vector_pro_exception("Out of range.");
            
            if (*iter == target)   return iterator_pro<value_type>(this->_data, iter.get_idx());
        }

        return iterator_pro<value_type>(this->_data, exclude_to.get_idx());
    }
    
    const_iterator_pro<value_type> find(const value_type& target, const_iterator_pro<value_type> from, const_iterator_pro<value_type> exclude_to) const {
        if (from.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (exclude_to.get_data() != this->_data)   throw vector_pro_exception("Iterator not of this vector.");
        if (this->data_len <= 0) return const_iterator_pro<value_type>(this->_data, exclude_to.get_idx());
        
        for (auto iter = from; iter != exclude_to; iter++) {
            if (iter.get_idx() < 0) throw vector_pro_exception("Out of range.");
            if (iter.get_idx() >= this->data_len) throw vector_pro_exception("Out of range.");
            
            if (*iter == target)   return const_iterator_pro<value_type>(this->_data, iter.get_idx());
        }

        return const_iterator_pro<value_type>(this->_data, exclude_to.get_idx());
    }
    
    // Built-in tim sort
    
    void sort(int(compare2)(const value_type &, const value_type &)) {
        if (this->_data == null || this->data_len <= 0) return;
        const int RUN = 32;
        size_type n = this->size();
        for (size_type i = 0; i < n; i += RUN)
            insertionSort(i, (i + 31 < n - 1) ? (i + 31) : (n - 1), compare2);

        for (size_type size = RUN; size < n; size = 2 * size) {
            for (size_type left = 0; left < n; left += 2 * size) {
                size_type mid = left + size - 1;
                size_type right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

                if (mid < right)
                    mergesort(left, mid, right, compare2);
            }
        }
    }

    void sort() {
        if (this->_data == null || this->data_len <= 0) return;
        
        int (*compare2)(const value_type &, const value_type &) = [](const value_type & a, const value_type & b) -> int {
            if (a > b)  return 1;
            else if (a < b) return -1;
            return 0;
        };
        
        const int RUN = 32;
        size_type n = this->size();
        for (size_type i = 0; i < n; i += RUN)
            insertionSort(i, (i + 31 < n - 1) ? (i + 31) : (n - 1), compare2);

        for (size_type size = RUN; size < n; size = 2 * size) {
            for (size_type left = 0; left < n; left += 2 * size) {
                size_type mid = left + size - 1;
                size_type right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

                if (mid < right)
                    mergesort(left, mid, right, compare2);
            }
        }
    }
    
    // Print methods
    
    void print(void(print)(value_type&)) const {
        printf("[ ");
        for (auto idx = 0; idx < this->data_len; idx++) {
            print(*(this->_data[idx]));
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

    friend std::ostream& operator<<(std::ostream &output, const vector_pro<value_type>& target) { 
        output << "[ ";
        for (auto citer = target.cbegin(); citer != target.cend(); citer++) {
            output << *citer;
            if (citer.get_idx() < target.size() - 1)    output << ", ";
        }
        if (target.size() == 0) output << "null";
        output << " ]";
        return output;            
    }
    
    void operator= (const vector_pro<value_type>& another) {
        this->destroy();
        size_type ini_size = another.capacity();
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.data_len;
        size_type idx = 0;
        for (auto iter = another.cbegin(); iter != another.cend(); iter++ ) {
            this->_data[idx] = new value_type(*iter);
            idx++;
        }
    }

    void operator= (vector_pro<value_type>&& another) {
        this->destroy();
        std::swap(this->_data, another._data);
        std::swap(this->data_len, another.data_len);
        std::swap(this->curr_size, another.curr_size);
    }

    void operator= (const std::vector<value_type>& another) {
        this->destroy();
        size_type ini_size = another.capacity();
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.data_len;
        size_type idx = 0;
        for (auto iter = another.cbegin(); iter != another.cend(); iter++ ) {
            this->_data[idx] = new value_type(*iter);
            idx++;
        }
    }

    void operator= (const std::initializer_list<value_type>& another) {
        this->destroy();
        size_type ini_size = another.size();
        if (ini_size < 0) {
            throw vector_pro_exception("Initial size of vector should be geq 0.");
            return;
        }
        this->_data = new value_type* [ini_size];
        if (this->_data == null) {
            throw vector_pro_exception("Out of memory.");
            return;
        }
        this->curr_size = ini_size;
        this->data_len = another.size();
        size_type idx = 0;
        for (auto iter = another.begin(); iter != another.end(); iter++ ) {
            this->_data[idx] = new value_type(*iter);
            idx++;
        }
    }

    // Iterators
    
    iterator_pro<value_type> begin() noexcept {
        return iterator_pro<value_type>(this->_data);
    }

    iterator_pro<value_type> end() noexcept {
        return iterator_pro<value_type>(this->_data, this->data_len);
    }

    iterator_pro<value_type> rbegin() noexcept {
        return iterator_pro<value_type>(this->_data, this->data_len - 1, true);
    }

    iterator_pro<value_type> rend() noexcept {
        return iterator_pro<value_type>(this->_data, -1, true);
    }

    const_iterator_pro<value_type> cbegin() const noexcept {
        return const_iterator_pro<value_type>(this->_data);
    }

    const_iterator_pro<value_type> cend() const noexcept {
        return const_iterator_pro<value_type>(this->_data, this->data_len);
    }

    const_iterator_pro<value_type> crbegin() const noexcept {
        return const_iterator_pro<value_type>(this->_data, this->data_len - 1, true);
    }

    const_iterator_pro<value_type> crend() const noexcept {
        return const_iterator_pro<value_type>(this->_data, -1, true);
    }

    // to std::vector
    std::vector<value_type> to_vector() {
        std::vector<value_type> ret;
        ret.reserve(this->data_len);
        for (size_type idx = 0; idx < this->data_len; idx++) {
            ret.push_back(*this->_data[idx]);
        }
        return ret;
    }

};

# endif