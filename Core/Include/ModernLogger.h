#ifndef __MODERN_LOGGER_H__
#define __MODERN_LOGGER_H__

#include <fstream>
#include <string>
#include <mutex>
#include <string_view>

#if __has_include(<format>)
    #include <format>
    using std::format;
    using std::vformat;
    using std::make_format_args;
#else
    #include <fmt/core.h>
    using fmt::format;
    using fmt::vformat;
    using fmt::make_format_args;
#endif

enum class LogLevel {
    Debug,
    Info,
    Warn,
    Error
};

class MLogger {
public:
    static MLogger *Instance() {
        static MLogger instance;
        return &instance;
    }

    void Open( const char *path );
    void CloseFile();

    template<typename... Args>
    void Debug( std::string_view fmt, Args&&... args ) {
        //std::string msg = std::vformat( fmt, std::make_format_args( args... ) );
        Write( LogLevel::Debug, vformat( fmt, make_format_args( args... ) ) );
    }

    template<typename... Args>
    void Info( std::string_view fmt, Args&&... args ) {
        //std::string msg = std::vformat( fmt, std::make_format_args( args... ) );
        Write( LogLevel::Info, vformat( fmt, make_format_args( args... ) ) );
    }

    template<typename... Args>
    void Warn( std::string_view fmt, Args&&... args ) {
        //std::string msg = std::vformat( fmt, std::make_format_args( args... ) );
        Write( LogLevel::Warn, vformat( fmt, make_format_args( args... ) ) );
    }

    template<typename... Args>
    void Error( std::string_view fmt, Args&&... args ) {
        //std::string msg = std::vformat( fmt, std::make_format_args( args... ) );
        Write( LogLevel::Error, vformat( fmt, make_format_args( args... ) ) );
    }

private:
    MLogger();
    ~MLogger() { }

    void Write( LogLevel level, const std::string &msg );
    std::string Timestamp() const;

    std::ofstream m_file;
    std::mutex m_mutex;
};

typedef MLogger TheMLogger;

#endif