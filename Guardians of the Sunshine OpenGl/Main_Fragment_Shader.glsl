#version 330 core

struct Light {
    vec3 color;
    float intensity;
    vec3 position;    
    vec3 direction;    
    float range;       
    float cutoff;     
    float outerCutoff; 
    int type;          
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;  
    float shininess;
    float alpha;
};

#define MAX_LIGHTS 10

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform Material material;
uniform vec3 viewPos;
uniform sampler2D shadowMap;  
uniform mat4 lightSpaceMatrix; 

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

// Function to calculate shadow
float ShadowCalculation(vec4 fragPosLightSpace) {
    // Transform fragment position to light space
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // Perspective divide
    projCoords = projCoords * 0.5 + 0.5; // Convert to [0,1] range
    
    // Sample the shadow map (depth texture) and compare the depth values
    float closestDepth = texture(shadowMap, projCoords.xy).r; // Get depth value from shadow map
    float currentDepth = projCoords.z; // Get current fragment depth in light space

    // Shadow bias to prevent shadow acne (depth fighting)
    float bias = 0.005;
    return currentDepth > closestDepth + bias ? 1.0 : 0.0; // If fragment is in shadow, return 1.0, else 0.0
}

void main() {
    // Hardcoded tangent and bitangent vectors (example values, adjust based on your object orientation)
    vec3 tangent = normalize(vec3(1.0, 0.0, 0.0));   // Tangent vector (adjust as necessary)
    vec3 bitangent = normalize(vec3(0.0, 1.0, 0.0));  // Bitangent vector (adjust as necessary)
    vec3 normal = normalize(Normal);  // Normal vector (passed from the vertex shader)

    // Sample the normal from the normal map and convert from [0, 1] range to [-1, 1] range
    vec3 normalMap = texture(material.normal, TexCoords).rgb;
    normalMap = normalize(normalMap * 2.0 - 1.0);  // Convert to [-1, 1]
    
    // Transform the normal from tangent space to world space using the TBN matrix
    mat3 TBN = mat3(tangent, bitangent, normal);  // Construct TBN matrix using hardcoded vectors
    vec3 norm = normalize(TBN * normalMap);  // Transform normal from normal map using TBN

    // Direction to viewer
    vec3 viewDir = normalize(viewPos - FragPos); 
    vec3 result = vec3(0.0);

    // Start lighting calculations for each light
    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir;
        float currentIntensity = lights[i].intensity;
        vec3 ambient, diffuse, specular;
        float diff = 0.0;
        float spec = 0.0;

        if (lights[i].type == 0) {
            // Directional light
            lightDir = normalize(-lights[i].direction);
        } else if (lights[i].type == 1) {
            // Point light
            lightDir = normalize(lights[i].position - FragPos);
            float distance = length(lights[i].position - FragPos);
            float attenuation = 1.0 / (1.0 + (distance / lights[i].range));
            currentIntensity *= attenuation;
        } else if (lights[i].type == 2) {
            // Spotlight
            lightDir = normalize(lights[i].position - FragPos);
            float theta = dot(lightDir, normalize(-lights[i].direction));
            float epsilon = lights[i].cutoff - lights[i].outerCutoff;
            float spotlightFactor = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
            currentIntensity *= spotlightFactor;
        }

        // Lambertian diffuse shading
        diff = max(dot(norm, lightDir), 0.2);

        // Phong specular shading
        vec3 reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        // Compute ambient, diffuse, and specular contributions
        ambient = 0.1 * lights[i].color * vec3(texture(material.diffuse, TexCoords));
        diffuse = currentIntensity * lights[i].color * diff * vec3(texture(material.diffuse, TexCoords));
        specular = currentIntensity * lights[i].color * spec * vec3(texture(material.specular, TexCoords));

        // Shadow mapping contribution
        vec4 fragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
        float shadow = ShadowCalculation(fragPosLightSpace);

        // Combine lighting with shadow
        result += (ambient + diffuse + specular) * (1.0 - shadow);
    }

    FragColor = vec4(result, material.alpha);
}
