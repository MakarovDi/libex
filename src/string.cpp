#ifdef HAVE_CONFIG_H
#   include "ex/config"
#endif


#include "ex/cprint"
#include "ex/string"
#include "ex/macro"
#include "ex/exception"


namespace ex
{


const size_t string::kFormatBufferSize = 2048;
const Char*  string::empty = L("");



#define FORMAT_INTERNAL(CharType, format_arg, format_value)                                                           \
    CharType buff[kFormatBufferSize];                                                                                 \
    va_list args;                                                                                                     \
                                                                                                                      \
    va_start(args, format_arg);                                                                                       \
    bool formatted = vsprint(buff, ARRAY_LENGTH(buff), format_value, args);                                           \
    va_end(args);                                                                                                     \
                                                                                                                      \
    if (!formatted)                                                                                                   \
        throw_formatted<string::FormatException>("vsprint failure! result larger than %d chars?", kFormatBufferSize); \
                                                                                                                      \
    return std::basic_string<CharType>(buff);


StringA string::FormatA(const char*    format, ...) { FORMAT_INTERNAL(char,    format, format);         }
StringA string::FormatA(const StringA& format, ...) { FORMAT_INTERNAL(char,    format, format.c_str()); }
StringW string::FormatW(const wchar_t* format, ...) { FORMAT_INTERNAL(wchar_t, format, format);         }
StringW string::FormatW(const StringW& format, ...) { FORMAT_INTERNAL(wchar_t, format, format.c_str()); }

String  string::Format (const Char*    format, ...) { FORMAT_INTERNAL(Char,    format, format);         }
String  string::Format (const String&  format, ...) { FORMAT_INTERNAL(Char,    format, format.c_str()); }


template <typename CharType>
std::basic_string<CharType> vFromatInternal(const CharType* format, va_list args)
{
    CharType buff[string::kFormatBufferSize];

    if (!vsprint(buff, ARRAY_LENGTH(buff), format, args))
        throw_formatted<string::FormatException>("vsprint failure! result larger than %d chars?",
                                                 string::kFormatBufferSize);

    return std::basic_string<CharType>(buff);
}


StringA string::FormatA(const char*    format, va_list args) { return vFromatInternal(format, args); }
StringA string::FormatA(const StringA& format, va_list args) { return FormatA(format.c_str(), args); }
StringW string::FormatW(const wchar_t* format, va_list args) { return vFromatInternal(format, args); }
StringW string::FormatW(const StringW& format, va_list args) { return FormatW(format.c_str(), args); }

String  string::Format (const Char*    format, va_list args) { return vFromatInternal(format, args); }
String  string::Format (const String&  format, va_list args) { return Format(format.c_str(), args);  }


}