#version 330 core

in vec3 TexCoords;  // Input texture coordinates from the vertex shader

out vec4 FragColor;  // Output color of the fragment

uniform samplerCube skybox;  // The cubemap texture

void main()
{
    // Sample the cubemap texture using the texture coordinates
    FragColor = texture(skybox, TexCoords);
}
