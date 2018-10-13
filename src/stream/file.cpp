#include "ex/stream/file"

#include <cstdio>
#include <stdexcept>
#include <string>

#include "ex/stream/file"
#include "ex/macro"
#include "ex/assert"


#ifdef _WIN32
#  include <io.h>
#include <ex/stream/file>


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


// TODO: C++17 string_view

FileStream::FileStream(const char* fname,
                       FileStream::OpenMode open_mode,
                       FileStream::Access   access_mode,
                       FileStream::Share    share_mode) : // TODO: all
   m_access(access_mode),
   m_opened(false),
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

    // TODO: set_share_mode(m_file);

    m_opened = true;
}


void FileStream::close_file()
{
    if (m_file != nullptr)
    {
        std::fclose((FILE*)m_file);
        m_file = nullptr;
    }

    m_opened   = false;
}


index_t FileStream::read(uint8_t* buffer, index_t read_bytes)
{
    index_t read = (index_t)std::fread(buffer, 1, size_t(read_bytes), (FILE*)m_file);
    // TODO: error check
    return read;
}


FileStream::byte FileStream::read_byte()
{
    // TODO
    int result = std::fgetc((FILE*)m_file);

    return FileStream::byte(result);
}


void FileStream::write(const uint8_t* buffer, index_t write_bytes)
{
    // TODO: range_check
    index_t written = (index_t)std::fwrite(buffer, 1, size_t(write_bytes), (FILE*)m_file);

    if (written != write_bytes)
        throw std::runtime_error("write operation failed");
}


void FileStream::write_byte(uint8_t value)
{
    int result = std::fputc(value, (FILE*)m_file);

    if (result == EOF)
        throw std::runtime_error("write error");
}


void FileStream::seek(index_t position, IStream::SeekMode mode)
{
    seek_validate(position, mode);

    const static int seek_mode[] = { SEEK_SET, SEEK_CUR, SEEK_END };

    // TODO: position range check
    int result = std::fseek((FILE*)m_file, long(position), seek_mode[mode]);
    if (result)
    {
        throw std::runtime_error("seek file failed");
    }
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
    // TODO: assert is open
    return std::feof((FILE*)m_file) != 0;
}


index_t FileStream::position() const
{
    // TODO: assert is open
    // TODO: assert range_check
    return index_t(ftell((FILE*)m_file));
}


bool FileStream::is_valid() const
{
    return ferror((FILE*)m_file) == 0;
}


index_t FileStream::size() const
{
     // TODO: assert m_file != nullptr

    long pos = ftell((FILE*)m_file);
    if (pos == -1)
        throw std::runtime_error("ftell failure");

    int result = fseek((FILE*)m_file, 0, SEEK_END);
    if (result != 0)
        throw std::runtime_error("fseek failure");

    long size = ftell((FILE*)m_file);
    if (size == -1)
        throw std::runtime_error("ftell failure");

    result = fseek((FILE*)m_file, pos, SEEK_SET);
    if (result != 0)
        throw std::runtime_error("fseek failure");

    // TODO: range_check
    return index_t(size);
}


void FileStream::seek_validate(index_t position, IStream::SeekMode mode)
{
    index_t abs_position;

    switch (mode)
    {
        case kBegin:
            // TODO: assert > 0 ?
            abs_position = position;
            break;
        case kOffset:
            abs_position = this->position() + position;
            break;
        case kEnd:
            // TODO: assert < 0 ?
            abs_position = size() + position;
            break;
        default:
            throw std::logic_error("invalid state");
    }

    if (abs_position < 0 || abs_position > size())
        throw std::out_of_range("seek to invalid position");
}

