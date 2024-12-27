#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 tex; // Texture coordinates input

out vec2 TexCoords; // Pass texture coordinates to the fragment shader

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    TexCoords = tex; // Pass texture coordinates directly
}
