#include "Logger.h"

#include <stdarg.h>
#include <time.h>
#include <Windows.h>
#include <cstdlib>

Logger *Logger::s_pInstance = 0;

Logger::Logger() {
	m_pFhandle = nullptr;
}

void Logger::Open( const char *path ) {
	char filename[MAX_SIZE_OF_MESSAGE];

	SYSTEMTIME st;
	GetSystemTime( &st );
	sprintf_s( filename, "%s\\%04d%02d%02d_%02d%02d%02d_%03d.log",
		path, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );

	// Open File directory
	errno_t err = fopen_s( &m_pFhandle, filename, "w" );
	if( err != 0 ) m_pFhandle = nullptr;
}

void Logger::Printf_message( const char *fmt, ... ) {
	va_list args;
	va_start( args, fmt );
	vprintf( fmt, args );
	va_end( args );
}

void Logger::LogError( const char *fmt, ... ) {
	va_list argp;
	char outputline[MAX_SIZE_OF_MESSAGE];

	if( fmt == nullptr ) return; // Exit early as nothing passed in

	va_start( argp, fmt );
	vsprintf_s( outputline, fmt, argp );
	va_end( argp );

	if( m_pFhandle != nullptr ) {
		SYSTEMTIME st;
		GetSystemTime( &st );
		fprintf( m_pFhandle, "%04d%02d%02d_%02d%02d%02d_%03d: ",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
		fprintf( m_pFhandle, outputline );
		fprintf( m_pFhandle, "\n" );
	}
	#ifdef _DEBUG
		printf( outputline );
		printf( "\n" );
	#endif
}

void Logger::Printf_tstamp( const char *fmt, ... ) {
	va_list argp;
	char outputline[MAX_SIZE_OF_MESSAGE];

	if( fmt == nullptr ) return; // Exit early as nothing passed in

	va_start( argp, fmt );
	vsprintf_s( outputline, fmt, argp );
	va_end( argp );

	if( m_pFhandle != nullptr ) {
		SYSTEMTIME st;
		GetSystemTime( &st );
		fprintf( m_pFhandle, "%04d%02d%02d_%02d%02d%02d_%03d: ",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
		fprintf( m_pFhandle, outputline );
		fprintf( m_pFhandle, "\n" );
	}
	printf( outputline, "\n" );
}

void Logger::Printf_ntstamp( const char *fmt, ... ) {
	va_list argp;
	char outputline[MAX_SIZE_OF_MESSAGE];

	if( fmt == nullptr ) return; // Exit early as nothing passed in

	va_start( argp, fmt );
	vsprintf_s( outputline, fmt, argp );
	va_end( argp );

	if( m_pFhandle != nullptr ) {
		fprintf( m_pFhandle, outputline );
		fprintf( m_pFhandle, "\n" );
	}
	printf( outputline, "\n" );
}

void Logger::CloseFile() {
	if( m_pFhandle != nullptr ) {
		fclose( m_pFhandle );
		m_pFhandle = nullptr;
	}
}