#include "stream_test_tools.hpp"

#include <ex/stream/file>


using namespace ex;


class file_stream : public tool::file_test_base
{
protected:
    virtual void TearDown() override
    {
        fs.close();
        tool::file_test_base::TearDown();
    }

protected:
    FileStream fs;
};


struct EmptyFileCase
{
    static const char*       data() { return nullptr; }
    static constexpr index_t size = 0;
};


TEST_F(file_stream, compatibility)
{
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreateNew,    FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kAppend,       FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreate,       FileStream::kRead), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kRead), std::runtime_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kOpenCreate,   FileStream::kRead), std::logic_error);

    tool::init_file<EmptyFileCase>(tmp_fname);

    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreateNew,    FileStream::kReadWrite), std::logic_error);
    ASSERT_THROW(FileStream(tmp_fname, FileStream::kCreateNew,    FileStream::kReadWrite), std::logic_error);
}


TEST_F(file_stream, read_byte)
{
    tool::init_file<test::ReadByteCase>(tmp_fname);
    fs = FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    test::ReadByteCase::check(fs);
}


TEST_F(file_stream, read)
{
    tool::init_file<test::ReadCase>(tmp_fname);
    fs = FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    test::ReadCase::check(fs);
}


TEST_F(file_stream, empty_file)
{
    tool::init_file<test::EmptyStreamCase>(tmp_fname);
    fs = FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    test::EmptyStreamCase::check(fs);
}


TEST_F(file_stream, write_byte)
{
    fs = FileStream(tmp_fname, FileStream::kOpenCreate, FileStream::kWrite);
    FileStream fs_result(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    test::WriteByteCase::check(fs, fs_result);
}


TEST_F(file_stream, write)
{
    fs = FileStream(tmp_fname, FileStream::kOpenCreate, FileStream::kWrite);
    FileStream fs_result(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    test::WriteCase::check(fs, fs_result);
}


TEST_F(file_stream, write_read)
{
    fs = FileStream(tmp_fname, FileStream::kOpenCreate, FileStream::kReadWrite);
    FileStream fs_result(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    test::WriteReadCase::check(fs, fs_result);
}


TEST_F(file_stream, seek)
{
    tool::init_file<test::SeekCase>(tmp_fname);
    fs = FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kReadWrite);

    test::SeekCase::check(fs);
}


TEST_F(file_stream, seek_oversize)
{
    tool::init_file<test::SeekOversizeCase>(tmp_fname);
    fs = FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kReadWrite);

    test::SeekOversizeCase::check(fs);
}


TEST_F(file_stream, seek_empty_file)
{
    tool::init_file<test::SeekEmptyCase>(tmp_fname);
    fs = FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kReadWrite);

    test::SeekEmptyCase::check(fs);
}


TEST_F(file_stream, write_extend)
{
    tool::init_file<test::WriteExtendCase>(tmp_fname);
    fs = FileStream(tmp_fname, FileStream::kOpenExisting, FileStream::kWrite);
    FileStream fs_result(tmp_fname, FileStream::kOpenExisting, FileStream::kRead);

    test::WriteExtendCase::check(fs, fs_result);
}
