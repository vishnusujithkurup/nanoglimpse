#pragma once

#include <memory>

#include <spdlog/logger.h>

#include "nanoglimpse/Core/Defs.h"

namespace ng::Core {
    class NG_API Log {
    public:
        static void Init();

        inline static spdlog::logger* GetEngineLogger() { return s_EngineLogger.get(); }
        inline static spdlog::logger* GetClientLogger() { return s_ClientLogger.get(); }
    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#if defined(NG_DEBUG)
    #define NG_INTERNAL_TRACE(...)  ::ng::Core::Log::GetEngineLogger()->trace(__VA_ARGS__)
    #define NG_INTERNAL_INFO(...)   ::ng::Core::Log::GetEngineLogger()->info(__VA_ARGS__)
    #define NG_TRACE(...)           ::ng::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define NG_INFO(...)            ::ng::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#else
    #define NG_INTERNAL_TRACE(...) 
    #define NG_INTERNAL_INFO(...) 
    #define NG_TRACE(...) 
    #define NG_INFO(...) 
#endif

#define NG_INTERNAL_WARN(...)      ::ng::Core::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define NG_INTERNAL_ERROR(...)     ::ng::Core::Log::GetEngineLogger()->error(__VA_ARGS__)
#define NG_INTERNAL_CRITICAL(...)  ::ng::Core::Log::GetEngineLogger()->critical(__VA_ARGS__)
#define NG_WARN(...)               ::ng::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NG_ERROR(...)              ::ng::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define NG_CRITICAL(...)           ::ng::Core::Log::GetClientLogger()->critical(__VA_ARGS__)