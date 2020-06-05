// Author: Darshan Sen (RaisinTen)

#include "Logger.hpp"

#include <ostream>
#include <vector>
#include <string>

namespace logger
{
    using std::vector;
    using std::string;
    using std::ostream;
    using std::endl;

    /*** class Log ***/

    Log::Log(const string& message)
        :
            m_message{message}
    {
    }

    Log::Log(const char* message)
        :
            m_message{message}
    {
    }

    ostream& operator<<(ostream& stream, const Log& log)
    {
        stream << log.m_message;
        return stream;
    }

    /*** class Logger ***/

    Logger::Logger()
        :
            m_logs{}
    {
    }

    Logger& Logger::get_instance()
    {
        static Logger instance;
        return instance;
    }

    bool Logger::empty() const
    {
        return m_logs.empty();
    }

    auto Logger::get_logs() const
    {
        return m_logs;
    }

    void Logger::emplace_back(const Log& log)
    {
        m_logs.emplace_back(log);
    }

    ostream& operator<<(ostream& stream, const Logger& logger)
    {
        for(const auto& log : logger.m_logs)
        {
            stream << log << endl;
        }

        return stream;
    }
}
