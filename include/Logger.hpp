// Author: Darshan Sen (RaisinTen)

#pragma once

#include <ostream>
#include <vector>
#include <string>

namespace logger
{
    using std::vector;
    using std::string;
    using std::ostream;

    class Log
    {
        string m_message;
    public:
        Log(const string& message);
        Log(const char* message);
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
        friend ostream& operator<<(ostream& stream, const Logger& logger);
    };
}
