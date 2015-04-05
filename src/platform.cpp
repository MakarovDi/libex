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


String platform::defs()
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


String platform::info()
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

	return result;
}

}