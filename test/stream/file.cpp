#include <gtest/gtest.h>
#include <ex/stream/file>
#include <ex/stream/tmp>

#include <cstdio>
#include <cstring>


#define ASSERT_MEMEQ(mem1, mem2, count) (memcmp(mem1, mem2, count) == 0)


using namespace ex;


class file_stream : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        tmp_fname_str = ex::generate_tmp_file_name();
        tmp_fname = tmp_fname_str.c_str();
    }


    virtual void TearDown() override
    {
        if (tmp_fname == nullptr) return;
        std::remove(tmp_fname);
    }

protected:
    std::string tmp_fname_str;
    const char* tmp_fname;
};


void create_empty_file(const char* fname)
{
    FILE* fid = std::fopen(fname, "wb");
    if (fid == nullptr)
        throw std::runtime_error("file creation failed");

    fclose(fid);
}


void fill_file(const char* fname, const char* content, int size)
{
    FILE* fid = std::fopen(fname, "wb");
    if (fid == nullptr)
        throw std::runtime_error("file creation failed");

    int count = (int)fwrite(content, (size_t)1, (size_t)size, fid);

    fclose(fid);

    if (count != size)
        throw std::runtime_error("file writing failed");
}


void read_file_content(const char* fname, char* buffer, int& size)
{
    FILE* fid = std::fopen(fname, "rb");
    if (fid == nullptr)
        throw std::runtime_error("file open failed");

    size = (int)fread(buffer, (size_t)1, (size_t)size, fid);

    fclose(fid);
}


TEST_F(file_stream, compatibility)
{
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreateNew,    FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kAppend,       FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreate,       FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kRead), std::runtime_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kOpenCreate,   FileStream::kRead), std::logic_error);

    create_empty_file(tmp_fname);

    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreateNew,    FileStream::kReadWrite), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreateNew,    FileStream::kReadWrite), std::logic_error);
}


TEST_F(file_stream, read_byte)
{
    fill_file(tmp_fname, "123", 4);

    FileStream fs(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    ASSERT_EQ(fs.size(), 4);
    ASSERT_EQ(fs.is_open(), true);

    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.position(), 0);

    ASSERT_EQ(fs.read_byte(), (uint8_t)'1');
    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.position(), 1);

    ASSERT_EQ(fs.read_byte(), (uint8_t)'2');
    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.position(), 2);

    ASSERT_EQ(fs.read_byte(), (uint8_t)'3');
    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.position(), 3);

    ASSERT_EQ(fs.read_byte(), (uint8_t)'\0');
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.position(), 4);

    fs.close();
}


TEST_F(file_stream, read)
{
    fill_file(tmp_fname, "123", 4);

    FileStream fs(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    ASSERT_EQ(fs.size(), 4);
    ASSERT_EQ(fs.is_open(), true);

    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.position(), 0);

    uint8_t buf[3];

    ASSERT_TRUE(fs.read(buf, 3) == 3);
    ASSERT_MEMEQ(buf, "123", 3);
    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.position(), 3);
    
    ASSERT_TRUE(fs.read(buf, 3) == 1);
    ASSERT_MEMEQ(buf, "\0", 1);
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.position(), 4);

    fs.close();
}


TEST_F(file_stream, empty_file)
{
    create_empty_file(tmp_fname);

    FileStream fs(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    ASSERT_EQ(fs.size(), 0);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.is_open(), true);

    fs.close();
}


TEST_F(file_stream, write_byte)
{
    FileStream fs(tmp_fname, FileStream::kOpenCreate, FileStream::kWrite);

    ASSERT_EQ(fs.size(), 0);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.is_open(), true);

    fs.write_byte((uint8_t)'1');
    ASSERT_EQ(fs.size(), 1);
    ASSERT_EQ(fs.position(), 1);
    ASSERT_EQ(fs.eos(), true);

    fs.write_byte((uint8_t)'2');
    ASSERT_EQ(fs.size(), 2);
    ASSERT_EQ(fs.position(), 2);
    ASSERT_EQ(fs.eos(), true);

    fs.write_byte((uint8_t)'3');
    ASSERT_EQ(fs.size(), 3);
    ASSERT_EQ(fs.position(), 3);
    ASSERT_EQ(fs.eos(), true);

    fs.write_byte((uint8_t)'\0');
    ASSERT_EQ(fs.size(), 4);
    ASSERT_EQ(fs.position(), 4);
    ASSERT_EQ(fs.eos(), true);

    fs.close();

    char buf[4];
    int size = 4;
    read_file_content(tmp_fname, buf, size);

    ASSERT_EQ(size, 4);
    ASSERT_MEMEQ(buf, "123\0", 4);
}


TEST_F(file_stream, write)
{
    FileStream fs(tmp_fname, FileStream::kOpenCreate, FileStream::kWrite);

    ASSERT_EQ(fs.size(), 0);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.is_open(), true);

    fs.write((uint8_t*)"123", 3);
    ASSERT_EQ(fs.size(), 3);
    ASSERT_EQ(fs.position(), 3);
    ASSERT_EQ(fs.eos(), true);

    fs.write((uint8_t*)"4\0", 2);
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 5);
    ASSERT_EQ(fs.eos(), true);

    fs.close();

    char buf[5];
    int size = 5;
    read_file_content(tmp_fname, buf, size);

    ASSERT_EQ(size, 5);
    ASSERT_MEMEQ(buf, "1234\0", 5);
}


TEST_F(file_stream, write_read)
{
    FileStream fs(tmp_fname, FileStream::kOpenCreate, FileStream::kReadWrite);

    ASSERT_EQ(fs.size(), 0);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.is_open(), true);

    fs.write((uint8_t*)"1234\0", 5);
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 5);
    ASSERT_EQ(fs.eos(), true);

    fs.seek(3, FileStream::SeekMode::kBegin);
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 3);
    ASSERT_EQ(fs.eos(), false);

    ASSERT_EQ(fs.read_byte(), (uint8_t)'4');
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 4);
    ASSERT_EQ(fs.eos(), false);

    fs.write_byte((uint8_t)'5');
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 5);
    ASSERT_EQ(fs.eos(), true);

    fs.close();

    char buf[5];
    int size = 5;
    read_file_content(tmp_fname, buf, size);

    ASSERT_EQ(size, 5);
    ASSERT_MEMEQ(buf, "12345", 5);
}


TEST_F(file_stream, seek)
{
    fill_file(tmp_fname, "12345", 5);

    FileStream fs(tmp_fname, FileStream::kOpenExisting, FileStream::kReadWrite);
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.is_open(), true);

    fs.seek(2, FileStream::SeekMode::kBegin);
    ASSERT_EQ(fs.position(), 2);
    ASSERT_EQ(fs.eos(), false);

    ASSERT_EQ(fs.read_byte(), (uint8_t)'3');
    ASSERT_EQ(fs.position(), 3);
    ASSERT_EQ(fs.eos(), false);

    fs.seek(-1, FileStream::SeekMode::kOffset);
    ASSERT_EQ(fs.position(), 2);
    ASSERT_EQ(fs.eos(), false);

    fs.write_byte((uint8_t)'0');
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 3);
    ASSERT_EQ(fs.eos(), false);

    fs.seek(0, FileStream::SeekMode::kEnd);
    ASSERT_EQ(fs.position(), 5);
    ASSERT_EQ(fs.eos(), true);

    fs.seek(-1, FileStream::SeekMode::kEnd);
    ASSERT_EQ(fs.position(), 4);
    ASSERT_EQ(fs.eos(), false);

    ASSERT_EQ(fs.read_byte(), (uint8_t)'5');
    ASSERT_EQ(fs.position(), 5);
    ASSERT_EQ(fs.eos(), true);

    fs.close();
}


TEST_F(file_stream, seek_oversize)
{
    fill_file(tmp_fname, "12345", 5);

    FileStream fs(tmp_fname, FileStream::kOpenExisting, FileStream::kReadWrite);
    ASSERT_EQ(fs.size(), 5);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.is_open(), true);

    ASSERT_THROW(fs.seek(8, FileStream::SeekMode::kBegin), std::logic_error);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), false);

    ASSERT_THROW(fs.seek(8, FileStream::SeekMode::kOffset), std::logic_error);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), false);

    ASSERT_THROW(fs.seek(-1, FileStream::SeekMode::kOffset), std::logic_error);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), false);

    ASSERT_THROW(fs.seek(-10, FileStream::SeekMode::kEnd), std::logic_error);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), false);

    fs.close();
}


TEST_F(file_stream, seek_empty_file)
{
    create_empty_file(tmp_fname);

    FileStream fs(tmp_fname, FileStream::kOpenExisting, FileStream::kReadWrite);
    ASSERT_EQ(fs.size(), 0);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.is_open(), true);

    fs.seek(0, FileStream::SeekMode::kBegin);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);

    fs.seek(0, FileStream::SeekMode::kOffset);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);

    fs.seek(0, FileStream::SeekMode::kOffset);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), true);

    fs.close();
}


TEST_F(file_stream, write_extend)
{
    fill_file(tmp_fname, "1234", 4);

    FileStream fs(tmp_fname, FileStream::kOpenExisting, FileStream::kWrite);
    ASSERT_EQ(fs.size(), 4);
    ASSERT_EQ(fs.position(), 0);
    ASSERT_EQ(fs.eos(), false);
    ASSERT_EQ(fs.is_open(), true);

    fs.seek(2, FileStream::SeekMode::kBegin);
    fs.write((uint8_t*)"8901", 4);
    ASSERT_EQ(fs.position(), 6);
    ASSERT_EQ(fs.eos(), true);
    ASSERT_EQ(fs.size(), 6);

    fs.close();

    char buf[6];
    int size = 6;
    read_file_content(tmp_fname, buf, size);

    ASSERT_MEMEQ(buf, "128901", 6);
}
