#version 330 core

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
    float alpha;
};

struct Light {
    vec3 position;      // Used for point/spot lights
    vec3 direction;     // Used for directional/spot lights
    vec3 color;
    float intensity;

    float constant;     // Attenuation factor for point/spot lights
    float linear;       // Attenuation factor for point/spot lights
    float quadratic;    // Attenuation factor for point/spot lights

    int type;           // 0 = directional, 1 = point, 2 = spot
    float cutoff;       // Cosine of the spot light cutoff angle
    float outerCutoff;  // Cosine of the spot light outer cutoff angle
};

#define MAX_LIGHTS 10
uniform Light lights[MAX_LIGHTS];


uniform vec3 viewPosition;
uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

out vec4 FragColor;

void main()
{
    // Sample the diffuse texture
    FragColor = texture(material.diffuse, TexCoords);
}
