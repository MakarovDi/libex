#include "ex/stream/memory"



ex::MemoryStream::byte ex::MemoryStream::read_byte()
{
    // TODO: assert
    if (eos())
        return ex::MemoryStream::byte();

    uint8_t value = m_data[m_position];

    m_position++;
    update_eos();

    return ex::MemoryStream::byte(value);
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
    switch (mode)
    {
        case kBegin:
            // TODO: assert > 0 ?
            break;
        case kOffset:
            position = this->position() + position;
            break;
        case kEnd:
            // TODO: assert < 0 ?
            position = size() + position;
            break;
        default:
            throw std::logic_error("invalid state");
    }

    if (position > size() || position < 0)
        throw std::out_of_range("seek to position out of stream");

    m_position = position;
    update_eos();
}
