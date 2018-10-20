#include "ex/stream/memory"

#include <stdexcept>
#include "ex/assert"



ex::MemoryStream::byte ex::MemoryStream::read_byte()
{
    ex::assert(is_open(), "stream must be opened");

    if (eos())
        return ex::MemoryStream::byte();

    uint8_t value = m_data[m_position];

    m_position++;
    update_eos();

    return ex::MemoryStream::byte(value);
}


index_t ex::MemoryStream::read(uint8_t* buffer, index_t read_bytes)
{
    ex::assert(is_open(), "stream must be opened");

    index_t readed = stream_rest() > read_bytes ? read_bytes : stream_rest();

    memcpy(buffer, &m_data[m_position], size_t(readed));

    m_position += readed;
    update_eos();

    return readed;
}


void ex::MemoryStream::write_byte(uint8_t value)
{
    ex::assert(is_open(), "stream must be opened");

    if (eos())
        throw std::logic_error("end of stream");

    m_data[m_position] = value;

    m_position++;
    update_eos();
}


void ex::MemoryStream::write(const uint8_t* buffer, index_t write_bytes)
{
    ex::assert(is_open(), "stream must be opened");

    if (write_bytes > stream_rest())
        throw std::logic_error("not enough space to write");

    memcpy(&m_data[m_position], buffer, size_t(write_bytes));

    m_position += write_bytes;
    update_eos();
}


void ex::MemoryStream::seek(index_t position, ex::IStream::SeekMode mode)
{
    switch (mode)
    {
        case kBegin:
            ex::assert<std::out_of_range>(position >= 0, "position must be >= 0 for SeekMode::kBegin");
            break;

        case kOffset:
            position = this->position() + position;
            break;

        case kEnd:
            ex::assert<std::out_of_range>(position <= 0, "position must be >= 0 for SeekMode::kEnd");
            position = size() + position;
            break;

        default:
            throw std::logic_error("invalid state");
    }

    ex::assert<std::out_of_range>(position <= size() && position >= 0, "seek to position out of stream");

    m_position = position;
    update_eos();
}
