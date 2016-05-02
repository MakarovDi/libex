#include "ex/assert"
#include <cassert>


namespace ex
{

    inline void assertm(bool expression, const char* message)
    {
        assert(expression && message);
    }


    inline void assertm(const char* message)
    {
        assert(false && message);
    }
}
