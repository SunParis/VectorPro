# pragma once

# ifndef null
# define null 0
# endif

# include <cstdint>

# ifndef VECTOR_PRO_ITER
# define VECTOR_PRO_ITER 1

# if __SIZEOF_POINTER__ == 4
    typedef int32_t LEN_TYPE;
# elif __SIZEOF_POINTER__ == 8
    typedef int64_t LEN_TYPE;
# else
    typedef long int LEN_TYPE;
# endif

template <typename T>
class iterator_pro {
private:
    T **data = null;
    LEN_TYPE curr_pos = 0;
    bool reverse_flag = 0;
public:
    
    iterator_pro() {
        // Do Nothing
    }

    iterator_pro(T **source, LEN_TYPE idx = 0, bool reverse_flag = 0) {
        this->data = source;
        this->curr_pos = idx;
        this->reverse_flag = reverse_flag;
    }
    
    LEN_TYPE get_idx() const {
        return this->curr_pos;
    }

    T** const get_data() const {
        return this->data;
    }

    bool get_reverse_flag() const {
        return this->reverse_flag;
    }
    
    iterator_pro operator++() {
        if (this->reverse_flag == 1)
            this->curr_pos--;
        else
            this->curr_pos++;
        
        return *this;
    }

    iterator_pro operator++(int) {
        iterator_pro<T> ret(this->data, this->curr_pos);
        
        if (this->reverse_flag == 1)
            this->curr_pos--;
        else
            this->curr_pos++;
        
        return ret;
    }
    
    iterator_pro operator--() {
        if (this->reverse_flag == 1)
            this->curr_pos++;
        else
            this->curr_pos--;
        
        return *this;
    }

    iterator_pro operator--(int) {
        iterator_pro<T> ret(this->data, this->curr_pos);
        
        if (this->reverse_flag == 1)
            this->curr_pos++;
        else
            this->curr_pos--;
        
        return ret;
    }

    iterator_pro operator+(const int step) {
        if (this->reverse_flag == 0) {
            iterator_pro<T> ret(this->data, this->curr_pos + step);
            return ret;
        }
        iterator_pro<T> ret(this->data, this->curr_pos - step);
        return ret;
    }

    iterator_pro operator-(const int step) {
        if (this->reverse_flag == 0) {
            iterator_pro<T> ret(this->data, this->curr_pos - step);
            return ret;
        }
        iterator_pro<T> ret(this->data, this->curr_pos + step);
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
class const_iterator_pro {
private:
    T **data = null;
    LEN_TYPE curr_pos = 0;
    bool reverse_flag = 0;
public:    
    const_iterator_pro() {
        // Do Nothing
    }

    const_iterator_pro(const iterator_pro<T>& another) {
        this->data = another.get_data();
        this->curr_pos = another.get_idx();
        this->reverse_flag = another.get_reverse_flag();
    }

    const_iterator_pro(T **source, LEN_TYPE idx = 0, bool reverse_flag = 0) {
        this->data = source;
        this->curr_pos = idx;
        this->reverse_flag = reverse_flag;
    }
    
    LEN_TYPE get_idx() const {
        return this->curr_pos;
    }

    T** const get_data() const {
        return this->data;
    }
    
    const_iterator_pro operator++() {
        if (this->reverse_flag == 1)
            this->curr_pos--;
        else
            this->curr_pos++;
        
        return *this;
    }

    const_iterator_pro operator++(int) {
        const_iterator_pro<T> ret(this->data, this->curr_pos);
        
        if (this->reverse_flag == 1)
            this->curr_pos--;
        else
            this->curr_pos++;
        
        return ret;
    }
    
    const_iterator_pro operator--() {
        if (this->reverse_flag == 1)
            this->curr_pos++;
        else
            this->curr_pos--;
        
        return *this;
    }

    const_iterator_pro operator--(int) {
        const_iterator_pro<T> ret(this->data, this->curr_pos);
        
        if (this->reverse_flag == 1)
            this->curr_pos++;
        else
            this->curr_pos--;
        
        return ret;
    }

    const_iterator_pro operator+(const int step) {
        if (this->reverse_flag == 0) {
            const_iterator_pro<T> ret(this->data, this->curr_pos + step);
            return ret;
        }
        const_iterator_pro<T> ret(this->data, this->curr_pos - step);
        return ret;
    }

    const_iterator_pro operator-(const int step) {
        if (this->reverse_flag == 0) {
            const_iterator_pro<T> ret(this->data, this->curr_pos - step);
            return ret;
        }
        const_iterator_pro<T> ret(this->data, this->curr_pos + step);
        return ret;
    }

    bool operator==(const const_iterator_pro<T>& another) const {
        return ((this->data == another.get_data()) && (this->curr_pos == another.get_idx()));
    }

    bool operator!=(const const_iterator_pro<T>& another) const {
        return ((this->data != another.get_data()) || (this->curr_pos != another.get_idx()));
    }

    const T& operator*() {
        return *(this->data[curr_pos]);
    }
};


# endif