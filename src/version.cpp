#include "ex/version"
#include "ex/macro"


#ifdef HAVE_CONFIG_H
#  include "ex/config"
#else
#  define VERSION_MAJOR    0
#  define VERSION_MINOR    0
#  define VERSION_REVISION 0
#endif


namespace ex
{


const uint8_t version::kMajor    = VERSION_MAJOR;
const uint8_t version::kMinor    = VERSION_MINOR;
const uint8_t version::kRevision = VERSION_REVISION;
const Char*   version::kString   = L("v") L(LITERAL(VERSION_MAJOR)) L(".") L(LITERAL(VERSION_MINOR)) L(".") L(LITERAL(VERSION_REVISION));


}

