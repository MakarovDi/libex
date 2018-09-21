#include <gtest/gtest.h>
#include <ex/stream/file>
#include <ex/stream/tmp>

#include <cstdio>


using namespace ex;


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


TEST(file_stream, compatibility)
{
    std::string tmp_fname = ex::generate_tmp_file_name();

    ASSERT_THROW(FileStream(tmp_fname.c_str(), FileStream::kCreateNew,    FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname.c_str(), FileStream::kAppend,       FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname.c_str(), FileStream::kCreate,       FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname.c_str(), FileStream::kOpenExisting, FileStream::kRead), std::runtime_error);
    ASSERT_THROW(FileStream(tmp_fname.c_str(), FileStream::kOpenCreate,   FileStream::kRead), std::logic_error);

    create_empty_file(tmp_fname.c_str());

    ASSERT_THROW(FileStream(tmp_fname.c_str(), FileStream::kCreateNew,    FileStream::kReadWrite), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname.c_str(), FileStream::kCreateNew,    FileStream::kReadWrite), std::logic_error);

    std::remove(tmp_fname.c_str());
}


TEST(file_stream, read_byte_test)
{
    std::string tmp_fname = ex::generate_tmp_file_name();
    fill_file(tmp_fname.c_str(), "123", 4);

    FileStream fs(tmp_fname.c_str(), FileStream::kOpenExisting, FileStream::kRead);

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

    std::remove(tmp_fname.c_str());
}

//TEST(file_stream, read_position)
//TEST(file_stream, write_position)
//TEST(file_stream, empty_file_position) // size, pos,  eos
