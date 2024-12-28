#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture()
    : textureID(0), width(0), height(0), nrChannels(0),
    minFilter(GL_LINEAR), magFilter(GL_LINEAR),
    wrapS(GL_REPEAT), wrapT(GL_REPEAT), anisotropy(1.0f) {}

Texture::~Texture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

bool Texture::LoadTexture(const std::string& filePath) {

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);


    glDepthMask(false);

    GLenum format = (nrChannels == 1) ? GL_RED : (nrChannels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return true;
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetTextureID() const {
    return textureID;
}

// Setters
void Texture::SetMinFilter(GLenum filter) {
    minFilter = filter;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
}

void Texture::SetMagFilter(GLenum filter) {
    magFilter = filter;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::SetWrapS(GLenum wrap) {
    wrapS = wrap;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
}

void Texture::SetWrapT(GLenum wrap) {
    wrapT = wrap;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}


GLenum Texture::GetMinFilter() const {
    return minFilter;
}

GLenum Texture::GetMagFilter() const {
    return magFilter;
}

GLenum Texture::GetWrapS() const {
    return wrapS;
}

GLenum Texture::GetWrapT() const {
    return wrapT;
}

float Texture::GetAnisotropy() const {
    return anisotropy;
}
