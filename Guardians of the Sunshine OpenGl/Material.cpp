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
    if (!shader) {
        shader = defaultShader;
    }

    if (enableBlend) {
        glEnable(GL_BLEND);
        glBlendFunc(blendSrcFactor, blendDstFactor);
    }
    else {
        glDisable(GL_BLEND);
    }

    if (enableBackFaceCulling) {
        glEnable(GL_CULL_FACE);
        glCullFace(cullFace);
        glFrontFace(GL_CCW);
    }
    else {
        glDisable(GL_CULL_FACE);
    }

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
    if (normalTexture) {
        normalTexture->Unbind();
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (specularTexture) {
        specularTexture->Unbind();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (diffuseTexture) {
        diffuseTexture->Unbind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    shader->SetUniform("material.shininess", 0.0f);
    shader->SetUniform("material.alpha", 1.0f);
}

void Material::SetBlendMode(GLenum srcFactor, GLenum dstFactor) {
    blendSrcFactor = srcFactor;
    blendDstFactor = dstFactor;
    enableBlend = true;  
}

void Material::SetBackFaceCulling(bool enable, GLenum face) {
    enableBackFaceCulling = enable;
    cullFace = face;
}
