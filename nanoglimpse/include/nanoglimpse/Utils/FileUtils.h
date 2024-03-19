#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Core/Log.h"

namespace ng::FileUtils {
    std::string NG_API loadFileToString(const char *filename) {
        std::ifstream in(filename);
        if (!in.is_open()) {
            NG_INTERNAL_ERROR("Failed to open file '{0}'!", filename);
            return "";
        }
        std::stringstream ss;
        ss << in.rdbuf();
        in.close();
        if (in.bad()) {
            NG_INTERNAL_ERROR("Failed to read file '{0}!", filename);
            return "";
        }
        return ss.str();
    }
}