#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
private:
    unsigned int textureID;
    std::string filePath;
    int width, height, channels;

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    unsigned int GetID() const { return textureID; }
};
