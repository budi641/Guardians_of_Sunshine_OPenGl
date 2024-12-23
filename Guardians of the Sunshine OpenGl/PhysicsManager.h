#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include "Entity.h"
#include "Shader.h"
#include <glad/glad.h>
#include"RenderManager.h"
#include "Vertex.h"

class PhysicsManager
{
private:

    float gravityScale;
    GLuint VAO, VBO;
    std::vector<DebugVertex> vertices;
    bool debug = false;
    Shader* debugShader = nullptr;
    

public:
    PhysicsManager();
    ~PhysicsManager();

    reactphysics3d::PhysicsCommon* physicsCommon;
    reactphysics3d::PhysicsWorld* physicsWorld;

    void Update(float deltaTime);

    void EnableDebuging();

    void UpdateDebugRendering(RenderManager* renderer);

    void SetGravityScale(float scale);
    reactphysics3d::RigidBody* CreateRigidBody(Entity* entity);
};
