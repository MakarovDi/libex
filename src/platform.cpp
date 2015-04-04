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



}