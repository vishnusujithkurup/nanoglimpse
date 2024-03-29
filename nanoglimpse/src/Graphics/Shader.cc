#include <vector>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "nanoglimpse/Graphics/Shader.h"
#include "nanoglimpse/Graphics/GLDebug.h"
#include "nanoglimpse/Core/Log.h"

namespace ng::Graphics {

    int Shader::GetUniformLocation(const std::string &name, unsigned int prog) {
        int loc = glGetUniformLocation(prog, name.c_str());
        if (loc == -1) {
            NG_INTERNAL_ERROR("Uniform '{0}' is either not found or begins with reserved prefix \"gl_\"!", name);
            return -1;
        }
        return loc;
    }

    std::string Shader::TypeString(unsigned int type) {
        switch (type) {
            case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
            case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
            default: return "UNKNOWN_SHADER";
        };
    }

    void Shader::ShowInfoLog(const std::string &shaderName, unsigned int ID, const std::string &type, bool stageFailed) {
        int len;
        if (type == "PROGRAM") {
            GLEC(glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &len));
            std::vector<GLchar> infoLog(len);
            GLEC(glGetProgramInfoLog(ID, len, &len, infoLog.data()));
            if (stageFailed) {
                NG_INTERNAL_ERROR("[Shader='{0}', stage=SHADER_PROGRAM] Linking Failed:\n{1}", shaderName, infoLog.data());
                GLEC(glDeleteProgram(ID));
            } else if (len>0) {
                NG_INTERNAL_WARN("[Shader='{0}', stage=SHADER_PROGRAM] Info Log:\n{1}", shaderName, infoLog.data());
            }
        } else {
            GLEC(glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &len));
            std::vector<GLchar> infoLog(len);
            GLEC(glGetShaderInfoLog(ID, len, &len, infoLog.data()));
            if (stageFailed) {
                NG_INTERNAL_ERROR("[Shader='{0}', stage={1}] Compilation Failed:\n{2}", shaderName, type, infoLog.data());
                GLEC(glDeleteShader(ID));
            } else if (len>0) {
                NG_INTERNAL_WARN("[Shader='{0}', stage={1}] Info Log:\n{2}", shaderName, type, infoLog.data());
            }
        }
    }

    unsigned int Shader::CreateShader(const std::string &shaderName, unsigned int type, const char *src) {
        unsigned int ID = glCreateShader(type);
        if (ID == 0) {
            NG_INTERNAL_ERROR("[Shader='{0}'] Failed to create shader of type={1}!", shaderName, TypeString(type));
            return 0;
        }
        GLEC(glShaderSource(ID, 1, &src, NULL));
        GLEC(glCompileShader(ID));
        int compileStatus;
        GLEC(glGetShaderiv(ID, GL_COMPILE_STATUS, &compileStatus));
        ShowInfoLog(shaderName, ID, TypeString(type), !compileStatus);
        return ID;
    }

    unsigned int Shader::CreateProgram(const std::string &shaderName, unsigned int vs, unsigned int fs) {
        unsigned int ID = glCreateProgram();
        if (ID == 0) {
            NG_INTERNAL_ERROR("[Shader='{0}'] Failed to create shader program!", shaderName);
            return 0;
        }
        GLEC(glAttachShader(ID, vs));
        GLEC(glAttachShader(ID, fs));
        GLEC(glLinkProgram(ID));
        int linkStatus;
        GLEC(glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus));
        ShowInfoLog(shaderName, ID, "PROGRAM", !linkStatus);
        return ID;
    }

    Shader::Shader(const std::string &name, const std::string &vertexCode, const std::string &fragmentCode) : m_Name(name) {
        unsigned int vs = CreateShader(m_Name, GL_VERTEX_SHADER, vertexCode.c_str());
        unsigned int fs = CreateShader(m_Name, GL_FRAGMENT_SHADER, fragmentCode.c_str());
        m_ID = CreateProgram(m_Name, vs, fs);
        GLEC(glDeleteShader(vs));
        GLEC(glDeleteShader(fs));
    }

    void Shader::Activate() const {
        GLEC(glUseProgram(m_ID));
    }

    void Shader::Deactivate() const {
        glUseProgram(0);
    }

    void Shader::UploadInt(const std::string &name, int value) const {
        GLEC(glUniform1i(GetUniformLocation(name, m_ID), value));
    }

    void Shader::UploadFloat(const std::string &name, float value) const {
        GLEC(glUniform1f(GetUniformLocation(name, m_ID), value));
    }

    void Shader::UploadVec2(const std::string &name, const glm::vec2 &value) const {
        GLEC(glUniform2f(GetUniformLocation(name, m_ID), value.x, value.y));
    }

    void Shader::UploadVec3(const std::string &name, const glm::vec3 &value) const {
        GLEC(glUniform3f(GetUniformLocation(name, m_ID), value.x, value.y, value.z));
    }

    void Shader::UploadVec4(const std::string &name, const glm::vec4 &value) const {
        GLEC(glUniform4f(GetUniformLocation(name, m_ID), value.x, value.y, value.z, value.w));
    }

    void Shader::UploadMat3(const std::string &name, const glm::mat3 &value) const {
        GLEC(glUniformMatrix3fv(GetUniformLocation(name, m_ID), 1, GL_FALSE, glm::value_ptr(value)));
    }

    void Shader::UploadMat4(const std::string &name, const glm::mat4 &value) const {
        GLEC(glUniformMatrix4fv(GetUniformLocation(name, m_ID), 1, GL_FALSE, glm::value_ptr(value)));
    }

    Shader::~Shader() {
        GLEC(glDeleteProgram(m_ID));
    }
}