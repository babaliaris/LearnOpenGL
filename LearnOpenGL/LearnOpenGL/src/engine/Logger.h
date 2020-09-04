#ifndef ENGINE_LOGGER_H
#define ENGINE_LOGGER_H
#include <spdlog/logger.h>
#include <memory>

namespace Engine
{
    class Logger
    {
        public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> GetLogger() {return m_logger;}

        private:
        static std::shared_ptr<spdlog::logger> m_logger;
        
    };
}


#define LOG_INFO(...) ::Engine::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Engine::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Engine::Logger::GetLogger()->error(__VA_ARGS__)

#endif