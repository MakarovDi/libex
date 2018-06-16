#include "ex/assert"

#include <iostream>
#include "ex/macro"


namespace ex
{
#ifdef NDEBUG

    void failure(const char* message)
    {
        UNUSED(message);
    }

    void failure(const wchar_t* message)
    {
        UNUSED(message);
    }

#else

    void failure(const char* message)
    {
        std::cerr << "something goes definitely wrong!" << std::endl << std::endl;
        std::cerr << "Message: " << message << std::endl;

        abort();
    }


    void failure(const wchar_t* message)
    {
        std::wcerr << L"something goes definitely wrong!" << std::endl << std::endl;
        std::wcerr << L"Message: " << message << std::endl;

        abort();
    }

#endif
}
