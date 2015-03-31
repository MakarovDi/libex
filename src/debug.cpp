#ifdef HAVE_CONFIG_H
#   include "ex/config"
#endif


#include "ex/debug"
#include "ex/string"


#ifdef WINDOWS
#   define WIN32_LEAN_AND_MEAN

#   include <stdarg.h>
#   include <windows.h>
#   include <imagehlp.h>
#endif



namespace ex
{


#ifdef WINDOWS

int OutputDebugStringF(const Char *format, ...)
{
	Char buffer[2048];

	va_list args;
	va_start(args, format);
	bool result = vsprint(buffer, sizeof(buffer), format, args);
	va_end(args);

	if (result) OutputDebugString(buffer);

	return result;
}

#endif


// TODO: protect calls to DbgHelp with critical section

static void win_trace()
{
	char symbol_buffer[sizeof(IMAGEHLP_SYMBOL) + 255];
	IMAGEHLP_SYMBOL *symbol = PIMAGEHLP_SYMBOL(symbol_buffer);

	HANDLE process = GetCurrentProcess();
	if (!SymInitialize(process, NULL, TRUE))
	{
		print("fail\n");
	}

	symbol->MaxNameLength   = 254;
	symbol->SizeOfStruct = sizeof( IMAGEHLP_SYMBOL ) + 255;

	DWORD dummy = 0;

	// StackWalk(IMAGE_FILE_MACHINE_I386, process, )
	if (SymGetSymFromAddr( process, (DWORD)win_trace , &dummy, symbol ))
	{
		print("Symbol: %s\n", symbol->Name);
	}
	else
	{
		DWORD gle = GetLastError();
		print("fail: %lu\n", gle);
	}

	SymCleanup(process);

//	SYMBOL_INFO* symbol = new ;

//	symbol               = ( SYMBOL_INFO * )calloc( sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
//	symbol->MaxNameLen   = 255;
//	symbol->SizeOfStruct = sizeof( SYMBOL_INFO );
//
//	for( i = 0; i < frames; i++ )
//	{
//		SymFromAddr( process, ( DWORD64 )( stack[ i ] ), 0, symbol );
//
//		printf( "%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address );
//	}
//
//	free( symbol );


}


void debug::trace()
{
#ifdef WINDOWS
	win_trace();
#elif defined(UNIX)
	unix_trace();
#else
#   error Unknown system
#endif
}


}
