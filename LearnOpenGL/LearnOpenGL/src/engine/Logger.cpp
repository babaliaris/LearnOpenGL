#include "pch.h"
#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{
    std::shared_ptr<spdlog::logger> Logger::m_logger;

    void Logger::Init()
    {
        m_logger = spdlog::stdout_color_mt("ENGINE");
    }
}