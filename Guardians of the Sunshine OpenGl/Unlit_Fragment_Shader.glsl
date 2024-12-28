#version 330 core

struct Light {
    vec3 color;
    float intensity;
    vec3 direction;    // Direction for directional/spotlight, position for point light
    float range;       // Range for point lights
    float cutoff;      // Inner cutoff for spotlights
    float outerCutoff; // Outer cutoff for spotlights
    int type;          // 0 = directional, 1 = point, 2 = spotlight
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;  // Normal map texture
    float shininess;
    float alpha;
};

#define MAX_LIGHTS 10

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform Material material;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;       // Interpolated normal vector
in vec2 TexCoords;    // Texture coordinates
in mat3 TBN;          // Tangent-Bitangent-Normal matrix for normal mapping

out vec4 FragColor;
void main()
{
    // Sample the diffuse texture
    FragColor = texture(material.diffuse, TexCoords);
}
