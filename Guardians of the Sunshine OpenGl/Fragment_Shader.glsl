#version 330 core

struct Light {
    vec3 color;
    float intensity;
    vec3 direction;
};

struct Material{
    sampler2D diffuseTex;
    sampler2D specularTex;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
    bool transparent;
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
    vec3 ambient = material.ambient * light.color * light.intensity;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction); // Assuming light.direction is from light to object
    float diff = max(dot(norm, lightDir), 0.3);
    vec3 diffuse = material.diffuse * diff * light.color * light.intensity;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.color * light.intensity;

    vec4 diffuseTex = texture(material.diffuseTex, TexCoord);
    vec4 specularTex = texture(material.specularTex, TexCoord);

    vec3 result = ambient + diffuse * diffuseTex.rgb + specular * specularTex.rgb;

    //float a =  material.alpha + diffuseTex.a;
    
    FragColor = vec4(result,material.alpha);
}
