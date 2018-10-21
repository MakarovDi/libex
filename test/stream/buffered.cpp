#include "stream_test_tools.hpp"

#include <ex/stream/memory>
#include <ex/stream/buffered>
#include <ex/stream/tmp>


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
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::SeekInputCase>());

    MemoryStream s_even(buf.get(), test::SeekInputCase::size);
    MemoryStream s_odd(buf.get(), test::SeekInputCase::size);
    MemoryStream s_big(buf.get(), test::SeekInputCase::size);

    InputBufferedStream<MemoryStream> bs_even(s_even, 1);
    InputBufferedStream<MemoryStream> bs_odd(s_odd, 2);
    InputBufferedStream<MemoryStream> bs_big(s_big);

    test::SeekInputCase::check(bs_even);
    test::SeekInputCase::check(bs_odd);
    test::SeekInputCase::check(bs_big);
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


TEST(buffered_output_stream, write_byte)
{
    std::unique_ptr<uint8_t[]> buf(new uint8_t[test::WriteByteCase::size]);

    MemoryStream s_small(buf.get(), test::WriteByteCase::size);
    MemoryStream s_even(buf.get(), test::WriteByteCase::size);
    MemoryStream s_odd(buf.get(), test::WriteByteCase::size);
    MemoryStream s_big(buf.get(), test::WriteByteCase::size);

    OutputBufferedStream<MemoryStream> bs_small(s_small, 1);
    OutputBufferedStream<MemoryStream> bs_even(s_even, 2);
    OutputBufferedStream<MemoryStream> bs_odd(s_odd, 3);
    OutputBufferedStream<MemoryStream> bs_big(s_big);

    test::WriteByteCase::check(bs_small, s_small);
    test::WriteByteCase::check(bs_even, s_even);
    test::WriteByteCase::check(bs_odd, s_odd);
    test::WriteByteCase::check(bs_big, s_big);
}


TEST(buffered_output_stream, write)
{
    std::unique_ptr<uint8_t[]> buf(new uint8_t[test::WriteCase::size]);

    MemoryStream s_small(buf.get(), test::WriteCase::size);
    MemoryStream s_even(buf.get(), test::WriteCase::size);
    MemoryStream s_odd(buf.get(), test::WriteCase::size);
    MemoryStream s_big(buf.get(), test::WriteCase::size);

    OutputBufferedStream<MemoryStream> bs_small(s_small, 1);
    OutputBufferedStream<MemoryStream> bs_even(s_even, 2);
    OutputBufferedStream<MemoryStream> bs_odd(s_odd, 3);
    OutputBufferedStream<MemoryStream> bs_big(s_big);

    test::WriteCase::check(bs_small, s_small);
    test::WriteCase::check(bs_even, s_even);
    test::WriteCase::check(bs_odd, s_odd);
    test::WriteCase::check(bs_big, s_big);
}


TEST(buffered_output_stream, seek_oversize)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::SeekOversizeCase>());

    MemoryStream s(buf.get(), test::SeekOversizeCase::size);
    OutputBufferedStream<MemoryStream> bs(s);

    test::SeekOversizeCase::check(bs);
}


TEST(buffered_output_stream, seek_empty)
{
    uint8_t buf[1] = {1};

    MemoryStream s(buf, 0);
    OutputBufferedStream<MemoryStream> bs(s);

    test::SeekEmptyCase::check(bs);
}


TEST(buffered_output_stream, write_extend)
{
    TmpFileStream fs_tmp1;
    TmpFileStream fs_tmp2;
    TmpFileStream fs_tmp3;
    TmpFileStream fs_tmp4;

    fs_tmp1.write((uint8_t*)test::WriteExtendCase::data(), test::WriteExtendCase::size);
    fs_tmp2.write((uint8_t*)test::WriteExtendCase::data(), test::WriteExtendCase::size);
    fs_tmp3.write((uint8_t*)test::WriteExtendCase::data(), test::WriteExtendCase::size);
    fs_tmp4.write((uint8_t*)test::WriteExtendCase::data(), test::WriteExtendCase::size);
    fs_tmp1.seek(0);
    fs_tmp2.seek(0);
    fs_tmp3.seek(0);
    fs_tmp4.seek(0);

    OutputBufferedStream<TmpFileStream> bs1(fs_tmp1);
    OutputBufferedStream<TmpFileStream> bs2(fs_tmp2, 1);
    OutputBufferedStream<TmpFileStream> bs3(fs_tmp3, 2);
    OutputBufferedStream<TmpFileStream> bs4(fs_tmp4, 3);

    test::WriteExtendCase::check(bs1, fs_tmp1);
    test::WriteExtendCase::check(bs2, fs_tmp2);
    test::WriteExtendCase::check(bs3, fs_tmp3);
    test::WriteExtendCase::check(bs4, fs_tmp4);
}


TEST(buffered_output_stream, empty)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::EmptyStreamCase>());

    MemoryStream s(buf.get(), test::EmptyStreamCase::size);
    OutputBufferedStream<MemoryStream> bs(s);

    test::EmptyStreamCase::check(bs);
}


TEST(buffered_output_stream, seek)
{
    std::unique_ptr<uint8_t[]> buf(init_buffer<test::SeekOutputCase>());

    MemoryStream s_small(buf.get(), test::SeekOutputCase::size);
    MemoryStream s_even(buf.get(), test::SeekOutputCase::size);
    MemoryStream s_odd(buf.get(), test::SeekOutputCase::size);
    MemoryStream s_big(buf.get(), test::SeekOutputCase::size);

    OutputBufferedStream<MemoryStream> bs_small(s_small, 1);
    OutputBufferedStream<MemoryStream> bs_even(s_even, 2);
    OutputBufferedStream<MemoryStream> bs_odd(s_odd, 3);
    OutputBufferedStream<MemoryStream> bs_big(s_big);

    test::SeekOutputCase::check(bs_small, s_small);
    test::SeekOutputCase::check(bs_even, s_even);
    test::SeekOutputCase::check(bs_odd, s_odd);
    test::SeekOutputCase::check(bs_big, s_big);
}