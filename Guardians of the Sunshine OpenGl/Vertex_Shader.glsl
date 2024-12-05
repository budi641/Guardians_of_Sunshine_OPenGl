#version 330 core

layout(location = 0) in vec3 a_Position;  // Vertex position
layout(location = 1) in vec3 a_Normal;    // Vertex normal

out vec3 FragPos;  // To pass position to fragment shader
out vec3 Normal;   // To pass normal to fragment shader
out vec4 FragPosLightSpace;  // To pass position in light space for shadow mapping

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat4 u_LightSpaceMatrix;

void main() {
    FragPos = vec3(u_Model * vec4(a_Position, 1.0));
    Normal = mat3(transpose(inverse(u_Model))) * a_Normal;

    FragPosLightSpace = u_LightSpaceMatrix * vec4(FragPos, 1.0);

    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}
