#include "ex/stream/interface"


index_t ex::IStream::abs_position(index_t position, ex::IStream::SeekMode mode) const
{
    index_t abs_position;

    switch (mode)
    {
        case kBegin:
            // TODO: assert > 0 ?
            abs_position = position;
            break;
        case kOffset:
            abs_position = this->position() + position;
            break;
        case kEnd:
            // TODO: assert < 0 ?
            abs_position = size() + position;
            break;
        default:
            throw std::logic_error("invalid state");
    }

    return abs_position;
}
