#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
private:
    unsigned int programID; 
    std::unordered_map<std::string, int> uniformLocationCache;  

    int GetUniformLocation(const std::string& name);  

public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void Bind() const;    
    void Unbind() const;  

    void SetUniform(const std::string& name, int value);
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, const glm::vec3& value);
    void SetUniform(const std::string& name, const glm::mat4& value);
    void SetUniform(const std::string& name, const unsigned int value);


    unsigned int GetProgramID();

private:
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateProgram(const std::string& vertexSource, const std::string& fragmentSource);
    std::string GetFileContents(const std::string& filename);
};
