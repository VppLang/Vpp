// Author: Darshan Sen (RaisinTen)

#include "Logger.hpp"
#include "IO.hpp"

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
    using std::endl;

    /*** class Log ***/

    const map<LogType, string> Log::mp
    {
        {LogType::error,    "\033[1;31;40m" "ERROR:"   "\033[0m" " "},
        {LogType::warning,  "\033[1;33;40m" "WARNING:" "\033[0m" " "},
        {LogType::note,     "\033[1;36;40m" "NOTE:"    "\033[0m" " "},
    };

    Log::Log(const LogType log_type, const string& message, const size_t line, const size_t char_number)
        :
            m_log_type{log_type},
            m_message{message},
            m_line{line},
            m_char_number{char_number}
    {
    }

    Log::Log(const LogType log_type, const char* message, const size_t line, const size_t char_number)
        :
            m_log_type{log_type},
            m_message{string{message}},
            m_line{line},
            m_char_number{char_number}
    {
    }

    ostream& operator<<(ostream& stream, const Log& log)
    {
        if(log.m_line)
        {
            stream << "\033[0;1;47m@Line " << log.m_line;
            if(log.m_char_number)
            {
                stream << ":" << log.m_char_number;
            }
            stream << ":\033[0m ";
        }

        stream
            << Log::mp.at(log.m_log_type)
            << "\033[1;3;37;40m" << log.m_message << "\033[0m"
            ;

        if(log.m_line)
        {
            const auto line{io::lines[log.m_line - 1]};
            stream << "\n\t\033[0m" << line << "\033[0m";

            if(log.m_char_number)
            {
                stream << "\n\t";
                for(size_t i = 0; i < log.m_char_number - 1; ++i)
                {
                    if(line[i] == '\t')
                    {
                        stream << "\t";
                    }
                    else
                    {
                        stream << " ";
                    }
                }
                stream << "\033[1;31;40m^\033[0m";
            }
        }
        
        stream << endl;

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

    void Logger::emplace_back(const LogType log_type, const string& message, const size_t line, const size_t char_number)
    {
        emplace_back({log_type, message, line, char_number});
    }

    void Logger::emplace_back(const LogType log_type, const char* message, const size_t line, const size_t char_number)
    {
        emplace_back(log_type, string{message}, line, char_number);
    }

    void Logger::clear()
    {
        m_logs.clear();
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
