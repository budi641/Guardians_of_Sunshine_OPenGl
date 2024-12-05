#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;  // Fragment position in light space

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform sampler2D u_DepthMap;
uniform mat4 u_LightSpaceMatrix;

struct Light {
    int type;          // Type of light (e.g., directional, point, etc.)
    vec3 color;        // Light color
    float intensity;   // Light intensity
    vec3 direction;    // Direction of the light (for directional lights)
};

uniform Light u_Light;

void main() {
    // Fetch the texture color
    vec3 texColor = texture(u_Texture, FragPos.xy).rgb;

    // Shadow computation logic
    float shadow = 0.0;

    // Get depth value from depth map (light's point of view)
    float closestDepth = texture(u_DepthMap, FragPosLightSpace.xy).r;

    // Current depth from fragment position in light space
    float currentDepth = FragPosLightSpace.z / FragPosLightSpace.w;

    // Shadow comparison: if current depth is greater than the closest depth, it's in shadow
    if (currentDepth > closestDepth + 0.005) {
        shadow = 1.0;  // In shadow
    }

    // Lighting calculation (example: diffuse + shadow)
    vec3 lighting = texColor * (1.0 - shadow) * u_Light.color * u_Light.intensity;

    FragColor = vec4(lighting, 1.0);
}
