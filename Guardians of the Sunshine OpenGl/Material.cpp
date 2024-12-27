#include "Material.h"

Material::Material(float shininess, float alpha,
    const std::string& diffusePath, const std::string& specularPath,
    const std::string& normalPath)
    : shininess(shininess), alpha(alpha) {
    if (!diffusePath.empty()) {
        diffuseTexture = new Texture();
        diffuseTexture->LoadTexture(diffusePath);
    }
    if (!specularPath.empty()) {
        specularTexture = new Texture();
        specularTexture->LoadTexture(specularPath);
    }
    if (!normalPath.empty()) {
        normalTexture = new Texture();
        normalTexture->LoadTexture(normalPath);
    }
}

void Material::Bind(Shader* defaultShader) {
    if (!shader)
    {
        shader = defaultShader;
    };

    shader->Bind();

    if (diffuseTexture) {
        glActiveTexture(GL_TEXTURE0);
        diffuseTexture->Bind();
        shader->SetUniform("material.diffuse", 0); 
    }

    if (specularTexture) {
        glActiveTexture(GL_TEXTURE1);
        specularTexture->Bind();
        shader->SetUniform("material.specular", 1); 
    }

    if (normalTexture) {
        glActiveTexture(GL_TEXTURE2);
        normalTexture->Bind();
        shader->SetUniform("material.normal", 2); 
    }

    shader->SetUniform("material.shininess", shininess);
    shader->SetUniform("material.alpha", alpha);
}
void Material::Unbind() const {
    if (diffuseTexture) {
        diffuseTexture->Unbind();
    }
    if (specularTexture) {
        specularTexture->Unbind();
    }
    if (normalTexture) {
        normalTexture->Unbind();
    }
}
