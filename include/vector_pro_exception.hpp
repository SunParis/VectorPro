# pragma once

# ifndef null
# define null 0
# endif


# include <string.h>
# include <exception>

# ifndef VECTOR_PRO_EXCEPTION
# define VECTOR_PRO_EXCEPTION

class vector_pro_exception: public std::exception {
private:
    char *str = null;
public:
    vector_pro_exception(const char *_str) {
        this->str = strdup(_str);
    }
    
    ~vector_pro_exception() override {
        if (this->str != null)  delete [] this->str;
        this->str = null;
    }
    
    const char* what() const throw() override {
        return this->str;
    }
};

# endif