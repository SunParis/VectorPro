# include <iostream>

# ifndef null
    # define null 0
# endif

# ifndef _TEST_
# define _TEST_ 1

typedef unsigned char test_data_type;
static test_data_type _data = 0;

class test_object {
public:
    test_data_type *data = null;
    unsigned int len = 0;
    test_object(unsigned int N) {
        this->len = N;
        this->data = new test_data_type[N];
        for (auto i = 0; i < N; i++) {
            this->data[i] = _data;
        }
        _data++;
    }
    test_object(const test_object& tmp) {
        this->data = new test_data_type[tmp.len];
        this->len = tmp.len;
        for (auto i = 0; i < tmp.len; i++) {
            this->data[i] = tmp.data[0];
        }
        _data++;
    }
    ~test_object() {
        if (this->data != null)
            delete [] this->data;
        this->data = null;
        
    }
    friend std::ostream& operator<<(std::ostream &output, const test_object& target) { 
        output << "# " << (int)target.data[0];
        return output;            
    }
};

class small_object {
public:
    test_data_type data;
    small_object() {
        this->data = _data;
        _data++;
    }
    small_object(const small_object& tmp) {
        this->data = tmp.data;
        _data++;
    }
    ~small_object() {
        //
    }
    friend std::ostream& operator<<(std::ostream &output, const small_object& target) { 
        output << "# " << (int)target.data;
        return output;            
    }
};

class big_object {
public:
    test_data_type data[100];
    big_object() {
        for (auto i = 0; i < 100; i++) {
            this->data[i] = _data;
        }
        _data++;
    }
    big_object(const big_object& tmp) {
        for (auto i = 0; i < 100; i++) {
            this->data[i] = tmp.data[0];
        }
        _data++;
    }
    ~big_object() {
        //
    }
    friend std::ostream& operator<<(std::ostream &output, const big_object& target) { 
        output << "# " << (int)target.data[0];
        return output;            
    }
};

class large_object {
public:
    test_data_type data[1000];
    large_object() {
        for (auto i = 0; i < 1000; i++) {
            this->data[i] = _data;
        }
        _data++;
    }
    large_object(const large_object& tmp) {
        for (auto i = 0; i < 1000; i++) {
            this->data[i] = tmp.data[0];
        }
        _data++;
    }
    ~large_object() {
        //
    }
    friend std::ostream& operator<<(std::ostream &output, const large_object& target) { 
        output << "# " << (int)target.data[0];
        return output;            
    }
};


# endif