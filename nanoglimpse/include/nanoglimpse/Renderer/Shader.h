#pragma once

#include <string>

#include <glm/glm.hpp>

#include "nanoglimpse/Core/Defs.h"

namespace ng::Renderer {
    class NG_API Shader {
    public:
        Shader(const std::string &name, const std::string &vertexCode, const std::string &fragmentCode);

        void Activate() const;
        void Deactivate() const;

        void UploadInt(const std::string &name, int value);
        void UploadFloat(const std::string &name, float value);
        void UploadVec2(const std::string &name, const glm::vec2 &value);
        void UploadVec3(const std::string &name, const glm::vec3 &value);
        void UploadVec4(const std::string &name, const glm::vec4 &value);
        void UploadMat3(const std::string &name, const glm::mat3 &value);
        void UploadMat4(const std::string &name, const glm::mat4 &value);

        ~Shader();

    private:
        unsigned int m_ID;
        std::string m_Name;

        static int GetUniformLocation(const std::string &name, unsigned int prog);
        static std::string TypeString(unsigned int type);
        static void ShowInfoLog(const std::string &shaderName, unsigned int ID, const std::string &type, bool stageFailed);
        static unsigned int CreateShader(const std::string &shaderName, unsigned int type, const char *src);
        static unsigned int CreateProgram(const std::string &shaderName, unsigned int vs, unsigned int fs);
    };
}