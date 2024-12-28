#version 330 core
#extension GL_ARB_separate_shader_objects: enable

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 norm;
layout(location = 3) in vec2 tex;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bitangent;
layout(location = 6) in ivec4 boneIds; 
layout(location = 7) in vec4 weights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out mat3 TBN;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    vec3 transformedNormal = vec3(0.0f);
    vec3 transformedTangent = vec3(0.0f);
    vec3 transformedBitangent = vec3(0.0f);

    for(int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        if(boneIds[i] == -1) 
            continue;

        if(boneIds[i] >= MAX_BONES) 
        {
            totalPosition = vec4(pos, 1.0f);
            transformedNormal = norm;
            transformedTangent = tangent;
            transformedBitangent = bitangent;
            break;
        }

        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos, 1.0f);
        totalPosition += localPosition * weights[i];

        mat3 boneTransform = mat3(finalBonesMatrices[boneIds[i]]);
        transformedNormal += boneTransform * norm * weights[i];
        transformedTangent += boneTransform * tangent * weights[i];
        transformedBitangent += boneTransform * bitangent * weights[i];
    }

    vec3 worldNormal = normalize(mat3(transpose(inverse(model))) * transformedNormal);
    vec3 worldTangent = normalize(mat3(transpose(inverse(model))) * transformedTangent);
    vec3 worldBitangent = normalize(mat3(transpose(inverse(model))) * transformedBitangent);

    TBN = mat3(worldTangent, worldBitangent, worldNormal);

    vec4 worldPosition = model * totalPosition;
    FragPos = vec3(worldPosition);
    Normal = worldNormal;
    TexCoords = tex;

    mat4 viewModel = view * model;
    gl_Position = projection * viewModel * totalPosition;
}
