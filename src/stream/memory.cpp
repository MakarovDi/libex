#include "ex/stream/memory"



uint8_t ex::MemoryStream::read_byte()
{
    // TODO: assert

    uint8_t value = m_data[m_position];

    m_position++;
    update_eos();

    return value;
}


index_t ex::MemoryStream::read(uint8_t* buffer, index_t read_bytes)
{
    // TODO: assert > 0

    index_t readed = stream_rest() > read_bytes ? read_bytes : stream_rest();

    memcpy(buffer, &m_data[m_position], size_t(readed));

    m_position += readed;
    update_eos();

    return readed;
}


void ex::MemoryStream::write_byte(uint8_t value)
{
    // TODO: assert !eos

    m_data[m_position] = value;

    m_position++;
    update_eos();
}


void ex::MemoryStream::write(const uint8_t* buffer, index_t write_bytes)
{
    // TODO: assert > 0
    // TODO: assert ?
    //    if (write_bytes > stream_rest())
    //        throw std::logic_error("not enough space to write");

    memcpy(&m_data[m_position], buffer, size_t(write_bytes));

    m_position += write_bytes;
    update_eos();
}


void ex::MemoryStream::seek(index_t position, ex::IStream::SeekMode mode)
{
    position = abs_position(position, mode);

    if (position > size() || position < 0)
        throw std::logic_error("seek to position out of stream");

    m_position = position;
    update_eos();
}
