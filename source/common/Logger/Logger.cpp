#include "precompheader.h"

#include "Logger.h"

#include <fmt/core.h>
#include <fmt/ostream.h>

// Logger
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // support for basic file logging
#include <spdlog/sinks/rotating_file_sink.h> // support for rotating file logging

using SinkPtr = std::shared_ptr<spdlog::sinks::basic_file_sink_mt>;
using LoggerPtr = std::shared_ptr<spdlog::logger>;

struct Logger::Impl
{
   //LoggerPtr my_logger = spdlog::rotating_logger_mt("file_logger", "logs/mylogfile", 1048576 * 5, 3);
   SinkPtr sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>();
   LoggerPtr my_logger = std::make_shared<spdlog::logger>("mylogger", sink);
};

Logger::Logger()
   //: m(std::make_unique<Impl>())
{
}

Logger::~Logger() = default;

void Logger::debug(std::string_view message)
{
   spdlog::debug("", 3.12);

   //m->my_logger->debug()
}

CallLogger::CallLogger(std::string_view message, std::string_view file)
{
   std::cout << "" << std::endl;
}
