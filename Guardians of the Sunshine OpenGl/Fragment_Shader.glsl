#version 330 core

struct Light {
    vec3 color;
    float intensity;
    vec3 direction;
};

struct Material {
    sampler2D diffuseTex;
    sampler2D specularTex;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    // Ambient
    vec3 ambient = material.ambient * light.color * light.intensity;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction); // Assuming light.direction is from light to object
    float diff = max(dot(norm, lightDir), 0.3);
    vec3 diffuse = material.diffuse * diff * light.color * light.intensity;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.color * light.intensity;

    // Texture sampling
    vec4 diffuseTex = texture(material.diffuseTex, TexCoord);
    vec4 specularTex = texture(material.specularTex, TexCoord);

    // Combine results
    vec3 result = ambient + diffuse * diffuseTex.rgb + specular * specularTex.rgb;
    FragColor = vec4(result, 1.0);
}
