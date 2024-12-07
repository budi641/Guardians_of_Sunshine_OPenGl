#include "AssetManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stb_image.h> 

std::unordered_map<std::string, GLuint> AssetManager::shaders;
std::unordered_map<std::string, GLuint> AssetManager::textures;
std::unordered_map<std::string, GLuint> AssetManager::models;

std::string AssetManager::ReadFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint AssetManager::LoadShader(const std::string& vertexPath, const std::string& fragmentPath) {
    if (shaders.find(vertexPath + fragmentPath) != shaders.end()) {
        return shaders[vertexPath + fragmentPath];
    }

    std::string vertexCode = ReadFile(vertexPath);
    std::string fragmentCode = ReadFile(fragmentPath);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    shaders[vertexPath + fragmentPath] = shaderProgram;
    return shaderProgram;
}

GLuint AssetManager::LoadTexture(const std::string& filePath) {
    if (textures.find(filePath) != textures.end()) {
        return textures[filePath];
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    textures[filePath] = textureID;
    return textureID;
}

GLuint AssetManager::LoadModel(const std::string& modelPath) {
    GLuint dummyModelID = 1;
    models[modelPath] = dummyModelID;
    return dummyModelID;
}

GLuint AssetManager::GetShader(const std::string& shaderName) {
    return shaders[shaderName];
}

GLuint AssetManager::GetTexture(const std::string& textureName) {
    return textures[textureName];
}

GLuint AssetManager::GetModel(const std::string& modelName) {
    return models[modelName];
}
