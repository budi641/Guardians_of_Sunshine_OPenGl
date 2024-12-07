#include "Material.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stdexcept>



Material::Material(const std::string& textureDir){
    TexturesPath = textureDir;
}

GLuint Material::loadTexture(const std::string& path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true); //flipity
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load texture data
        if (channels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return texture;
    }
    else {
        stbi_image_free(data);
        throw std::runtime_error("Failed to load texture at path: " + path);
    }
}

void Material::loadAllTextures() {
   
    
    std::string diffusePath = TexturesPath + "_diffuse.png";   // Adjust extension as needed
    std::string specularPath = TexturesPath + "_specular.png";  // Adjust extension as needed

    try {
        diffuseTex = loadTexture(diffusePath);  // Load diffuse texture
        specularTex = loadTexture(specularPath);  // Load specular texture
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error loading textures: " << e.what() << std::endl;
    }

}
