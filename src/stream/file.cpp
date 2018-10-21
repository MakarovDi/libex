#include "ex/stream/file"

#include <cstdio>
#include <stdexcept>
#include <string>

#include "ex/stream/file"
#include "ex/macro"
#include "ex/assert"
#include "ex/range_check"
#include "ex/platform/macro"


#ifdef PLATFORM_IS_WINDOWS
#  include <io.h>
#  define access  _access_s
#else
#  include <unistd.h>
#endif


using namespace ex;



static const bool compatibility[FileStream::kOpenModeCount][FileStream::kAccessCount - 1][2] =
{
    //           R                     W                     R+W
    //  !Exists    Exists      !Exists   Exists       !Exists   Exists
    { {  false,    true   }, {  false,   true    }, {  false,    true   }  }, // kOpenExisting
    { {  false,    true   }, {  true,    true    }, {  true,     true   }  }, // kOpenCreate
    { {  false,    false  }, {  true,    false   }, {  true,     false  }  }, // kCreateNew
    { {  false,    false  }, {  true,    true    }, {  true,     true   }  }, // kCreate
    { {  false,    false  }, {  true,    true    }, {  true,     true   }  }, // kAppend
};


static const bool check_existance[FileStream::kOpenModeCount] =
{
    false, // kOpenExisting
    true,  // kOpenCreate
    true,  // kCreateNew
    false, // kCreate
    false, // kAppend
};


static const char* mode_selector[FileStream::kOpenModeCount][FileStream::kAccessCount - 1][2] =
{
    //            R                     W                     R+W
    //    !Exists   Exists     !Exists    Exists      !Exists    Exists
    { {    "",     "rb"   }, {  "",       "rb+"  }, {  "",       "rb+"  }  }, // kOpenExisting
    { {    "",     "rb"   }, {  "wb",     "rb+"  }, { "wb+",     "rb+"  }  }, // kOpenCreate
    { {    "",      ""    }, {  "wb",      ""    }, { "wb+",      ""    }  }, // kCreateNew
    { {    "",      ""    }, {  "wb",     "wb"   }, { "wb+",     "wb+"  }  }, // kCreate
    { {    "",      ""    }, {  "ab",     "ab"   }, { "ab+",     "ab+"  }  }, // kAppend
};


static const char open_mode_str[FileStream::kOpenModeCount][sizeof(LITERAL(FileStream::kOpenExisting))] =
{
    LITERAL(FileStream::kOpenExisting),
    LITERAL(FileStream::kOpenCreate),
    LITERAL(FileStream::kCreateNew),
    LITERAL(FileStream::kCreate),
    LITERAL(FileStream::kAppend)
};


static const char access_mode_str[FileStream::kAccessCount-1][sizeof(LITERAL(FileStream::kReadWrite))] =
{
    LITERAL(FileStream::kRead),
    LITERAL(FileStream::kWrite),
    LITERAL(FileStream::kReadWrite),
};


static bool is_file_exists(const char* fname)
{
    //
    // TODO: locked file = no exists ?
    // TODO: C++17 std::filesystem::exists(fname);
    //
    return access(fname, 0) == 0;
}


FileStream::FileStream(const char* fname,
                       FileStream::OpenMode open_mode,
                       FileStream::Access   access_mode) :
   m_access(access_mode),
   m_opened(false),
   m_size(kInvalidSize),
   m_filename(fname)
{
    bool file_exists = check_existance[open_mode] ? is_file_exists(fname) : true;

    if (!compatibility[open_mode][access_mode - 1][file_exists])
    {
        std::string message = "[";
        message.append(open_mode_str[open_mode]);
        message.append("]+[");
        message.append(access_mode_str[access_mode - 1]);
        message.append("]+[");
        message.append(file_exists ? "file exists" : "file doesn't exist");
        message.append("] is incompatible case");

        throw std::logic_error(message);
    }

    const char* mode_str = mode_selector[open_mode][access_mode - 1][file_exists];

    m_file = (void*)std::fopen(fname, mode_str);
    if (!m_file)
        throw std::runtime_error("can't open file");

    m_opened = true;
}


void FileStream::close_file()
{
    if (m_file != nullptr)
    {
        std::fclose((FILE*)m_file);
        m_file = nullptr;
    }

    m_opened = false;
}


index_t FileStream::read(uint8_t* buffer, index_t read_bytes)
{
    ex::assert(is_open(), "file must be opened");
    ex::assert(is_readable(), "file must be open in read mode");
    ex::range_check<size_t>(read_bytes);

    index_t readed = (index_t)std::fread(buffer, 1, size_t(read_bytes), (FILE*)m_file);
    return readed;
}


FileStream::byte FileStream::read_byte()
{
    ex::assert(is_open(), "file must be opened");
    ex::assert(is_readable(), "file must be open in read mode");
    static_assert(EOF == FileStream::byte::kInvalidValue, "constant equivalence");

    int result = std::fgetc((FILE*)m_file);

    return FileStream::byte(result);
}


void FileStream::write(const uint8_t* buffer, index_t write_bytes)
{
    ex::assert(is_open(), "file must be opened");
    ex::assert(is_writable(), "file must be open in write mode");
    ex::range_check<size_t>(write_bytes);

    index_t written = (index_t)std::fwrite(buffer, 1, size_t(write_bytes), (FILE*)m_file);

    m_size = kInvalidSize; // request for size update

    if (written != write_bytes)
        throw std::runtime_error("write operation failed");
}


void FileStream::write_byte(uint8_t value)
{
    ex::assert(is_open(), "file must be opened");
    ex::assert(is_writable(), "file must be open in write mode");

    int result = std::fputc(value, (FILE*)m_file);

    if (result == EOF)
        throw std::runtime_error("write error");

    m_size = kInvalidSize; // request for size update
}


void FileStream::flush()
{
    if (m_file)
    {
        std::fflush((FILE*)m_file);
    }
}


bool FileStream::eos() const
{
    ex::assert(is_open(), "file must be opened");
    return std::feof((FILE*)m_file) != 0;
}


index_t FileStream::position() const
{
    ex::assert(is_open(), "file must be opened");

    auto pos = ftell((FILE*)m_file);
    ex::range_check<index_t>(pos);

    return index_t(pos);
}


bool FileStream::is_valid() const
{
    ex::assert(is_open(), "file must be opened");

    return ferror((FILE*)m_file) == 0;
}


index_t FileStream::size() const
{
    ex::assert(is_open(), "file must be opened");

    if (m_size != kInvalidSize) return m_size;

    long pos = ftell((FILE*)m_file);
    if (pos == -1)
        throw std::runtime_error("ftell failure");

    int result = fseek((FILE*)m_file, 0, SEEK_END);
    if (result != 0)
        throw std::runtime_error("fseek failure");

    long size = ftell((FILE*)m_file);
    if (size == -1L)
        throw std::runtime_error("ftell failure");

    result = fseek((FILE*)m_file, pos, SEEK_SET);
    if (result != 0)
        throw std::runtime_error("fseek failure");

    ex::range_check<index_t>(size);
    return index_t(size);
}


void FileStream::seek(index_t position, IStream::SeekMode mode)
{
    ex::assert(is_open(), "file must be opened");
    ex::range_check<long>(position);

    seek_validate(position, mode);

    const static int seek_mode[] = { SEEK_SET, SEEK_CUR, SEEK_END };

    int result = std::fseek((FILE*)m_file, long(position), seek_mode[mode]);
    if (result)
    {
        throw std::runtime_error("seek file failed");
    }
}


void FileStream::seek_validate(index_t position, IStream::SeekMode mode)
{
    index_t abs_position;

    switch (mode)
    {
        case kBegin:
            ex::assert<std::out_of_range>(position >= 0, "position must be >= 0 for SeekMode::kBegin");
            abs_position = position;
            break;

        case kOffset:
            abs_position = this->position() + position;
            break;

        case kEnd:
            ex::assert<std::out_of_range>(position <= 0, "position must be >= 0 for SeekMode::kEnd");
            abs_position = size() + position;
            break;

        default:
            throw std::logic_error("invalid state");
    }

    ex::assert<std::out_of_range>(abs_position <= size() && abs_position >= 0, "seek to position out of stream");
}

