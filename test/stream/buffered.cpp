#include "stream_test_tools.hpp"

#include <ex/stream/memory>
#include <ex/stream/buffered>


using namespace ex;


template <typename TestCase>
uint8_t* init_buffer()
{
    uint8_t* buf = new uint8_t[TestCase::size];
    std::memcpy(buf, TestCase::data(), TestCase::size);

    return buf;
}


TEST(buffered_input_stream, read_byte)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::ReadByteCase>());

    MemoryStream s_even(buf.get(), test::ReadByteCase::size);
    MemoryStream s_odd(buf.get(), test::ReadByteCase::size);
    MemoryStream s_big(buf.get(), test::ReadByteCase::size);

    InputBufferedStream<MemoryStream> bs_even(s_even, 2);
    InputBufferedStream<MemoryStream> bs_odd(s_odd, 3);
    InputBufferedStream<MemoryStream> bs_big(s_big);

    test::ReadByteCase::check(bs_even);
    test::ReadByteCase::check(bs_odd);
    test::ReadByteCase::check(bs_big);
}


TEST(buffered_input_stream, read)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::ReadCase>());

    MemoryStream s_even(buf.get(), test::ReadCase::size);
    MemoryStream s_odd(buf.get(), test::ReadCase::size);
    MemoryStream s_big(buf.get(), test::ReadCase::size);

    InputBufferedStream<MemoryStream> bs_even(s_even, 2);
    InputBufferedStream<MemoryStream> bs_odd(s_odd, 3);
    InputBufferedStream<MemoryStream> bs_big(s_big);

    test::ReadCase::check(bs_even);
    test::ReadCase::check(bs_odd);
    test::ReadCase::check(bs_big);
}


TEST(buffered_input_stream, empty)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::EmptyStreamCase>());

    MemoryStream s(buf.get(), test::EmptyStreamCase::size);
    InputBufferedStream<MemoryStream> bs(s);

    test::EmptyStreamCase::check(bs);
}



TEST(buffered_input_stream, seek)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::SeekCase>());

    MemoryStream s_even(buf.get(), test::SeekCase::size);
    MemoryStream s_odd(buf.get(), test::SeekCase::size);
    MemoryStream s_big(buf.get(), test::SeekCase::size);

    InputBufferedStream<MemoryStream> bs_even(s_even, 1);
    InputBufferedStream<MemoryStream> bs_odd(s_odd, 2);
    InputBufferedStream<MemoryStream> bs_big(s_big);

    test::SeekCase::check(bs_even);
    test::SeekCase::check(bs_odd);
    test::SeekCase::check(bs_big);
}


TEST(buffered_input_stream, seek_oversize)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::SeekOversizeCase>());

    MemoryStream s(buf.get(), test::SeekOversizeCase::size);
    InputBufferedStream<MemoryStream> bs(s);

    test::SeekOversizeCase::check(bs);
}


TEST(buffered_input_stream, seek_empty)
{
    uint8_t buf[1] = {1};

    MemoryStream s(buf, 0);
    InputBufferedStream<MemoryStream> bs(s);

    test::SeekEmptyCase::check(bs);
}
