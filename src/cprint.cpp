#ifdef HAVE_CONFIG_H
#   include "ex/config"
#endif

#include "ex/cprint"

#include <cstdio>


#define PRINT_INTERNAL(format)                          \
    va_list args;                                       \
    va_start(args, format);                             \
    int success = vprint(format, args);                 \
    va_end(args);                                       \
    return success > 0;

#define SPRINT_INTERNAL(buff, size, format)             \
    va_list args;                                       \
    va_start(args, format);                             \
    int success = vsprint(buff, size, format, args);    \
    va_end(args);                                       \
    return success > 0;


namespace ex
{

    bool print(const wchar_t* format, ...) noexcept
    {
        PRINT_INTERNAL(format);
    }

    bool print(const char* format, ...) noexcept
    {
        PRINT_INTERNAL(format);
    }

    bool vprint(const wchar_t* format, va_list args) noexcept
    {
        return vwprintf(format, args) > 0;
    }

    bool vprint(const char* format, va_list args) noexcept
    {
        return vprintf(format, args) > 0;
    }


    bool sprint(wchar_t* buff, size_t buff_size, const wchar_t* format, ...) noexcept
    {
        SPRINT_INTERNAL(buff, buff_size, format);
    }


    bool sprint(char* buff, size_t buff_size, const char* format, ...) noexcept
    {
        SPRINT_INTERNAL(buff, buff_size, format);
    }


    bool vsprint(wchar_t* buff, size_t buff_size, const wchar_t* format, va_list args) noexcept
    {
        return vsnwprintf(buff, buff_size, format, args) > 0;
    }


    bool vsprint(char* buff, size_t buff_size, const char* format, va_list args) noexcept
    {
        return vsnprintf(buff, buff_size, format, args) > 0;
    }

}