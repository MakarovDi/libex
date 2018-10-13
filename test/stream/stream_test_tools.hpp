#ifndef    EX_TEST_STREAM_TEST_TOOLS_HEADER
#   define EX_TEST_STREAM_TEST_TOOLS_HEADER

#include <gtest/gtest.h>

#include <ex/stream/interface>
#include <ex/stream/tmp>

#include <string>
#include <cstdio>
#include <cstring>


#define ASSERT_MEMEQ(mem1, mem2, count) (memcmp(mem1, mem2, count) == 0)


namespace tool
{


class file_test_base : public ::testing::Test
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


template <typename TestCase>
void init_file(const char* fname)
{
    FILE* fid = std::fopen(fname, "wb");
    if (fid == nullptr)
        throw std::runtime_error("file creation failed");

    int count = (int)fwrite(TestCase::data(), size_t(1), size_t(TestCase::size), fid);

    fclose(fid);

    if (count != TestCase::size)
        throw std::runtime_error("file writing failed");
}


}


namespace test
{
    

struct ReadByteCase
{
    static const char*       data() { static const char value[] = "123\0"; return  value; }
    static constexpr index_t size = 4;


    static void check(ex::IInputStream& s)
    {
        ASSERT_EQ(s.size(), 4);
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_readable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);

        ASSERT_FALSE(s.eos());
        ASSERT_EQ(s.position(), 0);

        ASSERT_TRUE(s.read_byte() == uint8_t('1'));
        ASSERT_FALSE(s.eos());
        if (s.is_seekable()) ASSERT_EQ(s.position(), 1);

        ASSERT_TRUE(s.read_byte() == uint8_t('2'));
        ASSERT_FALSE(s.eos());
        if (s.is_seekable()) ASSERT_EQ(s.position(), 2);

        ASSERT_TRUE(s.read_byte() == uint8_t('3'));
        ASSERT_FALSE(s.eos());
        if (s.is_seekable()) ASSERT_EQ(s.position(), 3);

        ASSERT_TRUE(s.read_byte() == uint8_t('\0'));
        if (s.is_seekable()) ASSERT_EQ(s.position(), 4);
        ASSERT_TRUE(s.eos() == !s);

        ASSERT_FALSE(s.read_byte().is_valid());
        ASSERT_TRUE(s.eos());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(!s);
    }
};


struct ReadCase
{
    static const char*       data() { static const char value[] = "123\0"; return  value; }
    static constexpr index_t size = 4;


    static void check(ex::IInputStream& s)
    {
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_readable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);

        ASSERT_FALSE(s.eos());
        if (s.is_seekable()) ASSERT_EQ(s.position(), 0);

        uint8_t buf[3];
        ASSERT_EQ(s.read(buf, 3), 3);
        ASSERT_MEMEQ(buf, data(), 3);
        ASSERT_FALSE(s.eos());
        if (s.is_seekable()) ASSERT_EQ(s.position(), 3);

        ASSERT_EQ(s.read(buf, size), 1);
        ASSERT_MEMEQ(buf, "\0", 1);
        ASSERT_TRUE(s.eos());
        ASSERT_TRUE(!s);
        if (s.is_seekable()) ASSERT_EQ(s.position(), size);

        ASSERT_EQ(s.read(buf, size), 0);
        ASSERT_TRUE(s.eos());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(!s);
        if (s.is_seekable()) ASSERT_EQ(s.position(), size);
    }
};


struct EmptyStreamCase
{
    static const char*       data() { return nullptr; }
    static constexpr index_t size = 0;


    static void check(const ex::IStream& s)
    {
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_valid());

        if (s.is_seekable())
            ASSERT_EQ(s.position(), 0);

        if (!s.is_sizeless())
            ASSERT_EQ(s.size(), 0);

        ASSERT_TRUE(s.eos() || !s.eos());
    }
};


struct WriteByteCase
{
    static const char*       data() { return nullptr; }
    static constexpr index_t size = 4;


    static void check(ex::IOutputStream& s, ex::IInputStream& result)
    {
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_writable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        if (s.is_seekable()) ASSERT_EQ(s.position(), 0);

        s.write_byte(uint8_t('1'));
        if (!s.is_sizeless()) ASSERT_TRUE(s.size() >= 1);
        if (s.is_seekable())  ASSERT_EQ(s.position(), 1);

        s.write_byte(uint8_t('2'));
        if (!s.is_sizeless()) ASSERT_TRUE(s.size() >= 2);
        if (s.is_seekable())  ASSERT_EQ(s.position(), 2);

        s.write_byte(uint8_t('3'));
        if (!s.is_sizeless()) ASSERT_TRUE(s.size() >= 3);
        if (s.is_seekable())  ASSERT_EQ(s.position(), 3);

        s.write_byte(uint8_t('\0'));
        if (!s.is_sizeless()) ASSERT_TRUE(s.size() == 4);
        if (s.is_seekable())  ASSERT_EQ(s.position(), 4);

        ASSERT_TRUE(s.eos() || !s.eos());

        s.flush();

        uint8_t buf[size];
        ASSERT_EQ(result.read(buf, size), size);
        ASSERT_MEMEQ(buf, "123\0", size);
    }
};


struct WriteCase
{
    static const char*       data() { return nullptr; }
    static constexpr index_t size = 5;


    static void check(ex::IOutputStream& s, ex::IInputStream& result)
    {
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_writable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        if (s.is_seekable()) ASSERT_EQ(s.position(), 0);

        s.write((uint8_t*)"123", 3);
        if (s.is_seekable()) ASSERT_EQ(s.position(), 3);
        if (!s.is_sizeless()) ASSERT_TRUE(s.size() >= 3);

        s.write((uint8_t*)"4\0", 2);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);
        if (s.is_seekable()) ASSERT_EQ(s.position(), size);

        ASSERT_TRUE(s.eos() || !s.eos());

        s.flush();

        uint8_t buf[size];
        ASSERT_EQ(result.read(buf, size), size);
        ASSERT_MEMEQ(buf, "1234\0", size);
    }
};


struct WriteReadCase
{
    static const char*       data() { return nullptr; }
    static constexpr index_t size = 5;


    static void check(ex::IIoStream& s, ex::IInputStream& result)
    {
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_writable());
        ASSERT_TRUE(s.is_seekable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        ASSERT_EQ(s.position(), 0);

        s.write((uint8_t*)"1234\0", size);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);
        ASSERT_EQ(s.position(), size);

        s.seek(3, ex::IStream::SeekMode::kBegin);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);
        ASSERT_EQ(s.position(), 3);

        ASSERT_TRUE(s.read_byte() == uint8_t('4'));
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);
        ASSERT_EQ(s.position(), 4);

        s.write_byte(uint8_t('5'));
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);
        ASSERT_EQ(s.position(), size);

        ASSERT_TRUE(s.eos() || !s.eos());

        s.flush();

        uint8_t buf[size];
        ASSERT_EQ(result.read(buf, size), size);
        ASSERT_MEMEQ(buf, "12345", size);
    }
};


struct SeekCase
{
    static const char*       data() { static const char value[] = "12345\0"; return  value; }
    static constexpr index_t size = 5;


    static void check(ex::IInputStream& s)
    {
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_seekable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        ASSERT_TRUE(!s.eos());
        ASSERT_EQ(s.position(), 0);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);

        s.seek(2, ex::IStream::SeekMode::kBegin);
        ASSERT_EQ(s.position(), 2);
        ASSERT_FALSE(s.eos());

        ASSERT_TRUE(s.read_byte() == uint8_t('3'));
        ASSERT_EQ(s.position(), 3);
        ASSERT_FALSE(s.eos());

        s.seek(-1, ex::IStream::SeekMode::kOffset);
        ASSERT_EQ(s.position(), 2);
        ASSERT_FALSE(s.eos());

        ASSERT_TRUE(s.read_byte() == uint8_t('3'));
        ASSERT_EQ(s.size(), size);
        ASSERT_EQ(s.position(), 3);
        ASSERT_FALSE(s.eos());

        s.seek(-1,  ex::IStream::SeekMode::kEnd);
        ASSERT_EQ(s.position(), 4);
        ASSERT_FALSE(s.eos());

        s.seek(0,  ex::IStream::SeekMode::kEnd);
        ASSERT_EQ(s.position(), size);
        ASSERT_TRUE(s.eos() || !s.eos());
        ASSERT_FALSE(s.read_byte());
        ASSERT_EQ(s.position(), size);
        ASSERT_TRUE(s.eos());

        s.seek(-1,  ex::IStream::SeekMode::kEnd);
        ASSERT_TRUE(s.read_byte() == uint8_t('5'));
        ASSERT_EQ(s.position(), size);
        ASSERT_FALSE(s.read_byte());
        ASSERT_EQ(s.position(), size);
        ASSERT_TRUE(s.eos());
    }
};

struct SeekOversizeCase
{
    static const char*       data() { static const char value[] = "12345\0"; return  value; }
    static constexpr index_t size = 5;


    static void check(ex::IStream& s)
    {
        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_seekable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        ASSERT_TRUE(!s.eos());
        ASSERT_EQ(s.position(), 0);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);

        ASSERT_THROW(s.seek(8, ex::IStream::SeekMode::kBegin), std::out_of_range);
        ASSERT_EQ(s.position(), 0);
        ASSERT_EQ(s.eos(), false);

        ASSERT_THROW(s.seek(8, ex::IStream::SeekMode::kOffset), std::out_of_range);
        ASSERT_EQ(s.position(), 0);
        ASSERT_EQ(s.eos(), false);

        ASSERT_THROW(s.seek(-1, ex::IStream::SeekMode::kOffset), std::out_of_range);
        ASSERT_EQ(s.position(), 0);
        ASSERT_EQ(s.eos(), false);

        ASSERT_THROW(s.seek(-10, ex::IStream::SeekMode::kEnd), std::out_of_range);
        ASSERT_EQ(s.position(), 0);
        ASSERT_EQ(s.eos(), false);
    }
};


struct SeekEmptyCase
{
    static const char*       data() { return nullptr; }
    static constexpr index_t size = 0;


    static void check(ex::IStream& s)
    {
        ASSERT_TRUE(s.is_seekable());
        ASSERT_TRUE(s.is_valid());
        ASSERT_EQ(s.position(), 0);
        ASSERT_TRUE(s.eos() || !s.eos());

        s.seek(0, ex::IStream::SeekMode::kBegin);
        ASSERT_EQ(s.position(), 0);

        s.seek(0, ex::IStream::SeekMode::kOffset);
        ASSERT_EQ(s.position(), 0);

        s.seek(0, ex::IStream::SeekMode::kOffset);
        ASSERT_EQ(s.position(), 0);
    }
};


struct WriteExtendCase
{
    static const char*       data() { static const char value[] = "1234"; return  value; }
    static constexpr index_t size = 4;


    static void check(ex::IOutputStream& s, ex::IInputStream& result)
    {
        ASSERT_TRUE(s.is_expandable());

        ASSERT_TRUE(s.is_open());
        ASSERT_TRUE(s.is_valid());
        ASSERT_TRUE(s);
        ASSERT_TRUE(!s.eos());
        ASSERT_TRUE(s.is_seekable());
        ASSERT_EQ(s.position(), 0);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), size);

        s.seek(2, ex::IStream::SeekMode::kBegin);
        s.write((uint8_t*)"8901", 4);
        ASSERT_EQ(s.position(), 6);
        if (!s.is_sizeless()) ASSERT_EQ(s.size(), 6);

        s.flush();

        uint8_t buf[6];
        ASSERT_EQ(result.read(buf, sizeof(buf)), sizeof(buf));
        ASSERT_MEMEQ(buf, "128901", sizeof(buf));
    }
};


}
#endif // EX_TEST_STREAM_TEST_TOOLS_HEADER
