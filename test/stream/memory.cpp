#include "stream_test_tools.hpp"

#include <cstring>
#include <ex/stream/memory>


using namespace ex;


template <typename TestCase>
std::unique_ptr<uint8_t[]> init_buffer()
{
    std::unique_ptr<uint8_t[]> buf(new uint8_t[TestCase::size]);
    std::memcpy(buf.get(), TestCase::data(), TestCase::size);

    return buf;
}


TEST(memory_stream, read_byte)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::ReadByteCase>());
    MemoryStream s(buf.get(), test::ReadByteCase::size);

    test::ReadByteCase::check(s);
}


TEST(memory_stream, read)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::ReadCase>());
    MemoryStream s(buf.get(), test::ReadCase::size);

    test::ReadCase::check(s);
}


TEST(memory_stream, empty)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::EmptyStreamCase>());
    MemoryStream s(buf.get(), test::EmptyStreamCase::size);

    test::EmptyStreamCase::check(s);
}


TEST(memory_stream, write_byte)
{
    uint8_t buf[test::WriteByteCase::size];
    MemoryStream s(buf, test::WriteByteCase::size);
    MemoryStream result(buf, test::WriteByteCase::size);

    test::WriteByteCase::check(s, result);
}


TEST(memory_stream, write)
{
    uint8_t buf[test::WriteCase::size];
    MemoryStream s(buf, test::WriteCase::size);
    MemoryStream result(buf, test::WriteCase::size);

    test::WriteCase::check(s, result);
}


TEST(memory_stream, write_read)
{
    uint8_t buf[test::WriteReadCase::size];
    MemoryStream s(buf, test::WriteReadCase::size);
    MemoryStream result(buf, test::WriteReadCase::size);

    test::WriteReadCase::check(s, result);
}


TEST(memory_stream, seek)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::SeekInputCase>());
    MemoryStream s(buf.get(), test::SeekInputCase::size);

    test::SeekInputCase::check(s);
}


TEST(memory_stream, seek_oversize)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::SeekOversizeCase>());
    MemoryStream s(buf.get(), test::SeekOversizeCase::size);

    test::SeekOversizeCase::check(s);
}


TEST(memory_stream, seek_empty)
{
    MemoryStream s;

    test::SeekEmptyCase::check(s);
}
