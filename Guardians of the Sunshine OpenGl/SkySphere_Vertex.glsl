#version 330 core

layout (location = 0) in vec3 aPos;  // Vertex positions

out vec3 TexCoords;  // Output texture coordinates to the fragment shader

uniform mat4 projection;
uniform mat4 view;

void main()
{
    // Remove translation part from the view matrix (to prevent the skybox from moving with the camera)
    gl_Position = projection * view * vec4(aPos, 1.0f);
    TexCoords = aPos;  // Pass the vertex position as texture coordinates
}
