#include <ex/stream/buffered>

#include "ex/stream/buffered"


ex::InputBufferedStream::InputBufferedStream(ex::IInputStream& stream, index_t buffer_size) :
    m_stream(&stream),
    m_buffer(new uint8_t[size_t(buffer_size)]),
    m_stream_size(stream.size()),
    m_buffer_size(buffer_size),
    m_buffered(0),
    m_buffer_index(0),
    m_eos(stream.eos())
{
    if (!stream.is_open())
        throw std::logic_error("stream must be opened");

    refresh_buffer();
}


uint8_t ex::InputBufferedStream::read_byte()
{
//  TODO: assert ?
//    if (eos())
//        throw std::runtime_error("eof reached or error when reading byte");

    uint8_t value = m_buffer[size_t(m_buffer_index++)];

    if (m_buffer_index == m_buffered)
    {
        refresh_buffer();
    }

    return value;
}


index_t ex::InputBufferedStream::read(uint8_t* buffer, index_t read_bytes)
{
    uint8_t* buf = m_buffer.get();

    if (read_bytes <= buffer_rest())
    {
        memcpy(buffer, &buf[m_buffer_index], size_t(read_bytes));
        m_buffer_index += read_bytes;

        if (m_buffer_index == m_buffered)
        {
            refresh_buffer();
        }

        return read_bytes;
    }

    memcpy(buffer, &buf[size_t(m_buffer_index)], size_t(buffer_rest()));
    index_t readed = buffer_rest();

    readed += m_stream->read(&buffer[readed], read_bytes - readed);

    refresh_buffer();

    return readed;
}


void ex::InputBufferedStream::refresh_buffer()
{
    m_buffer_index = 0;

    if (m_stream->eos())
    {
        m_eos = true;
        m_buffered = 0;
        return;
    }

    m_buffered = m_stream->read(m_buffer.get(), buffer_size());
}


void ex::InputBufferedStream::close()
{
    m_stream->close();

    m_eos = true;

    m_buffer_index = 0;
    m_buffered     = 0;
}


index_t ex::InputBufferedStream::position() const
{
    if (!m_stream) return 0;
    return m_stream->position() - m_buffered + m_buffer_index;
}


void ex::InputBufferedStream::seek(index_t position, ex::IStream::SeekMode mode)
{
    if (!m_stream) return;

    position = abs_position(position, mode);

    if (position > size() || position < 0)
        throw std::logic_error("seek to position out of file");

    if (position >= m_stream->position() - m_buffered && position < m_stream->position())
    {
        m_buffer_index += position - this->position();
        return;
    }

    m_stream->seek(position, SeekMode::kBegin);

    m_eos = false;
    refresh_buffer();
}


