# pragma once

# ifndef _VECTOR_PRO_

# define _VECTOR_PRO_ 1

# include <cstdint>

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

# include "include/vector_pro.hpp"
# include "include/vector_pro_iter.hpp"
# include "include/vector_pro_exception.hpp"

# endif