#include "ex/platform"



namespace ex
{


bool platform::is_unix()
{
#ifdef PLATFORM_IS_UNIX
    return true;
#else
    return false;
#endif
}


bool platform::is_windows()
{
#ifdef PLATFORM_IS_WINDOWS
    return true;
#else
    return false;
#endif
}


bool platform::is_linux()
{
#ifdef PLATFORM_IS_LINUX
    return true;
#else
    return false;
#endif
}


bool platform::is_bsd()
{
#ifdef PLATFORM_IS_BSD
    return true;
#else
    return false;
#endif
}


bool platform::is_apple()
{
#ifdef PLATFORM_IS_APPLE
    return true;
#else
    return false;
#endif
}


bool platform::is_posix()
{
#ifdef PLATFORM_IS_POSIX
    return true;
#else
    return false;
#endif
}


bool platform::is_android()
{
#ifdef PLATFORM_IS_ANDROID
    return true;
#else
    return false;
#endif
}


bool is_x64()
{
#ifdef PLATFORM_IS_x64
    return true;
#else
    return false;
#endif
}


bool is_x86()
{
#ifdef PLATFORM_IS_x86
    return true;
#else
    return false;
#endif
}


String platform::compiler_defs()
{
    String result = string::empty;

#ifdef unix
    result += L("unix\t\t: yes\n");
#else
    result += L("unix\t\t: no\n");
#endif
#ifdef __unix
    result += L("__unix\t\t: yes\n");
#else
    result += L("__unix\t\t: no\n");
#endif
#ifdef __unix__
    result += L("__unix__\t: yes\n");
#else
    result += L("__unix__\t: no\n");
#endif
#ifdef BSD
    result += L("BSD\t\t: yes\n");
#else
    result += L("BSD\t\t: no\n");
#endif
#ifdef __APPLE__
    result += L("__APPLE__\t: yes\n");
#else
    result += L("__APPLE__\t: no\n");
#endif
#ifdef __MACH__
    result += L("__MACH__\t: yes\n");
#else
    result += L("__MACH__\t: no\n");
#endif
#ifdef linux
    result += L("linux\t\t: yes\n");
#else
    result += L("linux\t\t: no\n");
#endif
#ifdef __linux
    result += L("__linux\t\t: yes\n");
#else
    result += L("__linux\t\t: no\n");
#endif
#ifdef __linux__
    result += L("__linux__\t: yes\n");
#else
    result += L("__linux__\t: no\n");
#endif
#ifdef __gnu_linux
    result += L("__gnu_linux\t: yes\n");
#else
    result += L("__gnu_linux\t: no\n");
#endif
#ifdef __CYGWIN__
    result += L("__CYGWIN__\t: yes\n");
#else
    result += L("__CYGWIN__\t: no\n");
#endif
#ifdef __CYGWIN32__
    result += L("__CYGWIN32__\t: yes\n");
#else
    result += L("__CYGWIN32__\t: no\n");
#endif
#ifdef __CYGWIN64__
    result += L("__CYGWIN64__\t: yes\n");
#else
    result += L("__CYGWIN64__\t: no\n");
#endif
#ifdef WIN32
    result += L("WIN32\t\t: yes\n");
#else
    result += L("WIN32\t\t: no\n");
#endif
#ifdef _WIN32
    result += L("_WIN32\t\t: yes\n");
#else
    result += L("_WIN32\t\t: no\n");
#endif
#ifdef __WIN32
    result += L("__WIN32\t\t: yes\n");
#else
    result += L("__WIN32\t\t: no\n");
#endif
#ifdef WIN64
    result += L("WIN64\t\t: yes\n");
#else
    result += L("WIN64\t\t: no\n");
#endif
#ifdef _WIN64
    result += L("_WIN64\t\t: yes\n");
#else
    result += L("_WIN64\t\t: no\n");
#endif
#ifdef __WIN64
    result += L("__WIN64\t\t: yes\n");
#else
    result += L("__WIN64\t\t: no\n");
#endif
#ifdef __MINGW32__
    result += L("__MINGW32__\t: yes\n");
#else
    result += L("__MINGW32__\t: no\n");
#endif
#ifdef __MINGW64__
    result += L("__MINGW64__\t: yes\n");
#else
    result += L("__MINGW64__\t: no\n");
#endif
#ifdef __ANDROID__
    result += L("__ANDROID__\t: yes\n");
#else
    result += L("__ANDROID__\t: no\n");
#endif

    return result;
}


String platform::defs()
{
    String result = string::empty;

#ifdef PLATFORM_IS_UNIX
    result += L("PLATFORM_IS_UNIX\t: yes\n");
#else
    result += L("PLATFORM_IS_UNIX\t: no\n");
#endif
#ifdef PLATFORM_IS_APPLE
    result += L("PLATFORM_IS_APPLE\t: yes\n");
#else
    result += L("PLATFORM_IS_APPLE\t: no\n");
#endif
#ifdef PLATFORM_IS_WINDOWS
    result += L("PLATFORM_IS_WINDOWS\t: yes\n");
#else
    result += L("PLATFORM_IS_WINDOWS\t: no\n");
#endif
#ifdef PLATFORM_IS_LINUX
    result += L("PLATFORM_IS_LINUX\t: yes\n");
#else
    result += L("PLATFORM_IS_LINUX\t: no\n");
#endif
#ifdef PLATFORM_IS_POSIX
    result += L("PLATFORM_IS_POSIX\t: yes\n");
#else
    result += L("PLATFORM_IS_POSIX\t: no\n");
#endif
#ifdef PLATFORM_IS_BSD
    result += L("PLATFORM_IS_BSD\t\t: yes\n");
#else
    result += L("PLATFORM_IS_BSD\t\t: no\n");
#endif
#ifdef PLATFORM_IS_ANDROID
    result += L("PLATFORM_IS_ANDROID\t: yes\n");
#else
    result += L("PLATFORM_IS_ANDROID\t: no\n");
#endif

    result += L("\n");

#if defined(COMPILER_IS_CLANG)
    result += L("COMPILER_IS_CLANG\n");
#elif defined(COMPILER_IS_INTEL)
    result += L("COMPILER_IS_INTEL\n");
#elif defined(COMPILER_IS_HP)
    result += L("COMPILER_IS_HP\n");
#elif defined(COMPILER_IS_IBM)
    result += L("COMPILER_IS_IBM\n");
#elif defined(COMPILER_IS_MSC)
    result += L("COMPILER_IS_MSC\n");
#elif defined(COMPILER_IS_PORTLAND)
    result += L("COMPILER_IS_PORTLAND\n");
#elif defined(COMPILER_IS_SUN)
    result += L("COMPILER_IS_SUN\n");
#elif defined(COMPILER_IS_GNU)
    result += L("COMPILER_IS_GNU\n");
#endif

    result += L("\n");

#if defined(ENVIRONMENT_IS_CYGWIN)
    result += L("ENVIRONMENT_IS_CYGWIN\n");
#elif defined(ENVIRONMENT_IS_MINGW)
    result += L("ENVIRONMENT_IS_MINGW\n");
#else
    result += L("ENVIRONMENT_IS_NATIVE\n");
#endif

    result += L("\n");

#if defined(PROCESSOR_IS_IA64)
    result += L("PROCESSOR_IS_IA64\n");
#elif defined(PROCESSOR_IS_POWERPC)
    result += L("PROCESSOR_IS_POWERPC\n");
#elif defined(PROCESSOR_IS_SPARC)
    result += L("PROCESSOR_IS_SPARC\n");
#endif

#if defined(PLATFORM_IS_x64)
    result += L("PLATFORM_IS_x64\n");
#elif defined(PLATFORM_IS_x86)
    result += L("PLATFORM_IS_x86\n");
#endif

    return result;
}

}