#include <spdlog/sinks/stdout_color_sinks.h>

#include "nanoglimpse/Core/Log.h"

namespace ng::Core {
    std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        s_EngineLogger = spdlog::stdout_color_mt("NANOGLIMPSE");
        s_ClientLogger = spdlog::stdout_color_mt("APPLICATION");

        s_EngineLogger->set_pattern("%^[%L%Y%m%d %H:%M:%S.%f %n] %v%$");
        s_ClientLogger->set_pattern("%^[%L%Y%m%d %H:%M:%S.%f %n] %v%$");

        s_EngineLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}