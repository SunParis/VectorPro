# include <iostream>

# ifndef null
    # define null 0
# endif

# ifndef _TEST_
# define _TEST_ 1

typedef unsigned char test_data_type;
static test_data_type _data = 0;

class small_object {
public:
    test_data_type data;
    small_object() {
        this->data = _data;
        _data++;
    }
    small_object(test_data_type ddd) {
        this->data = ddd;
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

class medium_object {
public:
    test_data_type data[100];
    medium_object() {
        for (auto i = 0; i < 100; i++) {
            this->data[i] = _data;
        }
        _data++;
    }
    medium_object(test_data_type ddd) {
        for (auto i = 0; i < 100; i++) {
            this->data[i] = ddd;
        }
        _data++;
    }
    medium_object(const medium_object& tmp) {
        for (auto i = 0; i < 100; i++) {
            this->data[i] = tmp.data[0];
        }
        _data++;
    }
    ~medium_object() {
        //
    }
    friend std::ostream& operator<<(std::ostream &output, const medium_object& target) { 
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
    large_object(test_data_type ddd) {
        for (auto i = 0; i < 1000; i++) {
            this->data[i] = ddd;
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