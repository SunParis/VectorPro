# pragma once

# ifndef null
# define null 0
# endif

# include <cstdint>
# include <type_traits>

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

# ifndef _ITERATOR_PRO_
# define _ITERATOR_PRO_ 1

template <class value_type> class const_iterator_pro;

template <class value_type>
class iterator_pro {
private:

    value_type **data = null;
    size_type curr_pos = 0;
    bool reverse_flag = 0;

public:
    
    iterator_pro() {
        static_assert(!std::is_const<value_type>::value, "When the value_type is const, use const_iterator_pro instead.");
    }
    
    iterator_pro(const iterator_pro<value_type>& another) {
        static_assert(!std::is_const<value_type>::value, "When the value_type is const, use const_iterator_pro instead.");
        this->data = another.get_data();
        this->curr_pos = another.get_idx();
        this->reverse_flag = another.get_reverse_flag();
    }

    iterator_pro(value_type **source, size_type idx = 0, bool reverse_flag = 0) {
        static_assert(!std::is_const<value_type>::value, "When the value_type is const, use const_iterator_pro instead.");
        this->data = source;
        this->curr_pos = idx;
        this->reverse_flag = reverse_flag;
    }
    
    size_type get_idx() const {
        return this->curr_pos;
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
        iterator_pro<value_type> ret(this->data, this->curr_pos);
        
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
        iterator_pro<value_type> ret(this->data, this->curr_pos);
        
        if (this->reverse_flag == 1)
            this->curr_pos++;
        else
            this->curr_pos--;
        
        return ret;
    }

    iterator_pro operator+(const int step) {
        if (this->reverse_flag == 0) {
            iterator_pro<value_type> ret(this->data, this->curr_pos + step);
            return ret;
        }
        iterator_pro<value_type> ret(this->data, this->curr_pos - step);
        return ret;
    }

    iterator_pro operator-(const int step) {
        if (this->reverse_flag == 0) {
            iterator_pro<value_type> ret(this->data, this->curr_pos - step);
            return ret;
        }
        iterator_pro<value_type> ret(this->data, this->curr_pos + step);
        return ret;
    }

    bool operator==(const iterator_pro<value_type>& another) const {
        return ((this->data == another.get_data()) && (this->curr_pos == another.get_idx()));
    }

    bool operator!=(const iterator_pro<value_type>& another) const {
        return ((this->data != another.get_data()) || (this->curr_pos != another.get_idx()));
    }

    value_type& operator*() {
        return *(this->data[curr_pos]);
    }

    value_type** const get_data() const {
        return this->data;
    }

};

template <class value_type>
class const_iterator_pro {
private:

    value_type **data;
    size_type curr_pos = 0;
    bool reverse_flag = 0;

public:    
    const_iterator_pro() {
        // Do Nothing
    }

    const_iterator_pro(const const_iterator_pro<value_type>& another) {
        this->data = another.get_data();
        this->curr_pos = another.get_idx();
        this->reverse_flag = another.get_reverse_flag();
    }
    
    const_iterator_pro(const iterator_pro<value_type>& another) {
        this->data = another.get_data();
        this->curr_pos = another.get_idx();
        this->reverse_flag = another.get_reverse_flag();
    }

    const_iterator_pro(value_type **source, size_type idx = 0, bool reverse_flag = 0) {
        this->data = source;
        this->curr_pos = idx;
        this->reverse_flag = reverse_flag;
    }
    
    size_type get_idx() const {
        return this->curr_pos;
    }

    bool get_reverse_flag() const {
        return this->reverse_flag;
    }
    
    const_iterator_pro operator++() {
        if (this->reverse_flag == 1)
            this->curr_pos--;
        else
            this->curr_pos++;
        
        return *this;
    }

    const_iterator_pro operator++(int) {
        const_iterator_pro<value_type> ret(this->data, this->curr_pos);
        
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
        const_iterator_pro<value_type> ret(this->data, this->curr_pos);
        
        if (this->reverse_flag == 1)
            this->curr_pos++;
        else
            this->curr_pos--;
        
        return ret;
    }

    const_iterator_pro operator+(const int step) {
        if (this->reverse_flag == 0) {
            const_iterator_pro<value_type> ret(this->data, this->curr_pos + step);
            return ret;
        }
        const_iterator_pro<value_type> ret(this->data, this->curr_pos - step);
        return ret;
    }

    const_iterator_pro operator-(const int step) {
        if (this->reverse_flag == 0) {
            const_iterator_pro<value_type> ret(this->data, this->curr_pos - step);
            return ret;
        }
        const_iterator_pro<value_type> ret(this->data, this->curr_pos + step);
        return ret;
    }

    bool operator==(const const_iterator_pro<value_type>& another) const {
        return ((this->data == another.get_data()) && (this->curr_pos == another.get_idx()));
    }

    bool operator!=(const const_iterator_pro<value_type>& another) const {
        return ((this->data != another.get_data()) || (this->curr_pos != another.get_idx()));
    }

    const value_type& operator*() {
        return *(this->data[curr_pos]);
    }

    value_type** const get_data() const {
        return this->data;
    }
};


# endif