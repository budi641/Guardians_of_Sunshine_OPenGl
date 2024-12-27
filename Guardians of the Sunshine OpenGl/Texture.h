#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool LoadTexture(const std::string& filePath);
    void Bind() const;
    void Unbind() const;
    GLuint GetTextureID() const;

private:
    GLuint textureID;
    int width, height, nrChannels;
};
