# include <iostream>
# include <sys/time.h>
# include <ctime>

# ifndef _TIME_STRUCT_
# define _TIME_STRUCT_ 1

struct time_struct
{
    std::size_t start = 0;
    std::size_t build = 0;
    std::size_t end = 0;
};

struct write_struct
{
    std::size_t build_time = 0;
    std::size_t run_time = 0;
};

# endif
