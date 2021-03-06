#include "ex/version"
#include "ex/macro"


#ifdef UNICODE
#  define __L(s) L##s
#else
#  define __L(s) s
#endif

// L - conversion to project's encoding
#define L(S)    __L(S)


#ifdef HAVE_CONFIG_H
#  include "ex/config"
#else
#  define VERSION_MAJOR    0
#  define VERSION_MINOR    4
#  define VERSION_REVISION 0
#endif


namespace ex
{
    const uint8_t version::kMajor    = VERSION_MAJOR;
    const uint8_t version::kMinor    = VERSION_MINOR;
    const uint8_t version::kRevision = VERSION_REVISION;
    const Char*   version::kString   = L("v") LITERAL(VERSION_MAJOR) "." LITERAL(VERSION_MINOR) "." LITERAL(VERSION_REVISION);
}

