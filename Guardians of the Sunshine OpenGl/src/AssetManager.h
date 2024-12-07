#pragma once
#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>  
#include <glad/glad.h>   

class AssetManager {
public:
    static GLuint LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
    static GLuint LoadTexture(const std::string& filePath);
    static GLuint LoadModel(const std::string& modelPath);

    static GLuint GetShader(const std::string& shaderName);
    static GLuint GetTexture(const std::string& textureName);
    static GLuint GetModel(const std::string& modelName);

private:
    static std::string ReadFile(const std::string& filePath);

    static std::unordered_map<std::string, GLuint> shaders;
    static std::unordered_map<std::string, GLuint> textures;
    static std::unordered_map<std::string, GLuint> models;
};
