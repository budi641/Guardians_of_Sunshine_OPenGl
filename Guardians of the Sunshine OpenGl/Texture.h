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

    void SetMinFilter(GLenum filter);
    void SetMagFilter(GLenum filter);
    void SetWrapS(GLenum wrap);
    void SetWrapT(GLenum wrap);

    GLenum GetMinFilter() const;
    GLenum GetMagFilter() const;
    GLenum GetWrapS() const;
    GLenum GetWrapT() const;

private:
    GLuint textureID;
    int width, height, nrChannels;

    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapS;
    GLenum wrapT;

};
