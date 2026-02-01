#include "ModernLogger.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

std::string LevelToString( LogLevel level ) {
    switch( level ) {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warn:
        return "WARN";
    case LogLevel::Error:
        return "ERROR";
    default:
        break;
    }
    return "UNKNOWN";
}

MLogger::MLogger() : m_file() {

}

void MLogger::Open( const char *path ) {
    std::string filename = format( "{}/{}.log", path, Timestamp() );
    m_file.open( filename, std::ios::out );
}

void MLogger::CloseFile() {
    std::scoped_lock lock( m_mutex );
    if( m_file.is_open() ) {
        m_file.close();
    }
}

void MLogger::Write( LogLevel level, const std::string &msg ) {
    std::scoped_lock lock( m_mutex );
    
    std::string line = format( "{} [{}] {}", Timestamp(), LevelToString( level ), msg );

    if( m_file.is_open() ) {
        m_file << line << "\n";
    }

    std::cout << line << "\n";
}

std::string MLogger::Timestamp() const {
    auto now = std::chrono::system_clock::now();
    auto ms = duration_cast<std::chrono::milliseconds>( now.time_since_epoch() ) % 1000;

    std::time_t t = std::chrono::system_clock::to_time_t( now );
    std::tm tm{};

    localtime_s( &tm, &t );

    std::ostringstream oss;
    oss << std::put_time( &tm, "%Y%m%d_%H%M%S" )
        << "_" << std::setw( 3 ) << std::setfill( '0' ) << ms.count();

    return oss.str();
}