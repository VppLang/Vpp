// Author: Darshan Sen (RaisinTen)

#pragma once

#include <ostream>
#include <vector>
#include <string>
#include <map>

namespace logger
{
    using std::vector;
    using std::string;
    using std::ostream;
    using std::map;

    enum class LogType
    {
        error,
        warning,
        note,
    };

    class Log
    {
        const static map<LogType, string> mp;
        LogType m_log_type;
        string m_message;
        size_t m_line;
        size_t m_char_number;
    public:
        Log(const LogType log_type, const string& message, const size_t line = 0u, const size_t char_number = 0u);
        Log(const LogType log_type, const char* message, const size_t line = 0u, const size_t char_number = 0u);
        friend ostream& operator<<(ostream& stream, const Log& log);
    };

    class Logger
    {
        Logger();
        vector<Log> m_logs;
    public:
        static Logger& get_instance();
        Logger(const Logger&) = delete;
        void operator=(const Logger&) = delete;
        bool empty() const;
        auto get_logs() const;
        void emplace_back(const Log& log);
        void emplace_back(const LogType log_type, const string& message, const size_t line = 0u, const size_t char_number = 0u);
        void emplace_back(const LogType log_type, const char* message, const size_t line = 0u, const size_t char_number = 0u);
        void clear();
        friend ostream& operator<<(ostream& stream, const Logger& logger);
    };
}
