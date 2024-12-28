#include "PhysicsManager.h"
#include "Entity.h"
#include "TransformComponent.h"



PhysicsManager::PhysicsManager()
{
    physicsCommon = new reactphysics3d::PhysicsCommon();
    reactphysics3d::PhysicsWorld::WorldSettings settings;
    physicsWorld = physicsCommon->createPhysicsWorld(settings);
    gravityScale = 1.0f;


}

PhysicsManager::~PhysicsManager()
{
    delete physicsCommon;
}

void PhysicsManager::Update(float deltaTime)
{


    try {
        physicsWorld->update(deltaTime);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception during PhysicsWorld update: " << e.what() << std::endl;
    }
    
}

void PhysicsManager::EnableDebuging()
{
    debug = true;
    physicsWorld->setIsDebugRenderingEnabled(true);
    debugShader = new Shader("debug.vs", "debug.fs");

    reactphysics3d::DebugRenderer& debugRenderer = physicsWorld->getDebugRenderer();

    debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
    debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);
    debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
    debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



}

void PhysicsManager::UpdateDebugRendering(RenderManager* renderer)
{
    if (!debug)
    {
        return;
    }

    reactphysics3d::DebugRenderer& debugRenderer = physicsWorld->getDebugRenderer();

    debugShader->Bind();
    vertices.clear();
    auto* lines = debugRenderer.getLinesArray();

    for (int i = 0; i < debugRenderer.getNbLines(); i++)
    {
        DebugVertex vertex(lines[i].point1);
        vertices.push_back(vertex);
        vertex = lines[i].point2;
        vertices.push_back(vertex);

    }

    renderer->camera->UpdateProjection(*debugShader);




    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DebugVertex), &vertices[0], GL_STREAM_DRAW);


    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertices.size());
    glBindVertexArray(0);

    vertices.clear();
    auto* triangles = debugRenderer.getTrianglesArray();

    for (int i = 0; i < debugRenderer.getNbTriangles(); i++)
    {
        DebugVertex vertex(triangles[i].point1);
        vertices.push_back(vertex);
        vertex = triangles[i].point2;
        vertices.push_back(vertex);
        vertex = triangles[i].point3;
        vertices.push_back(vertex);

    }


    renderer->camera->UpdateProjection(*debugShader);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DebugVertex), &vertices[0], GL_STREAM_DRAW);


    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertices.size());
    glBindVertexArray(0);


}

void PhysicsManager::SetGravityScale(float scale)
{
    gravityScale = scale;
    glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);
    reactphysics3d::Vector3 rpGravity(gravity.x, gravity.y, gravity.z);
    physicsWorld->setGravity(rpGravity * gravityScale);
}

reactphysics3d::RigidBody* PhysicsManager::CreateRigidBody(Entity* entity)
{
    TransformComponent* transformComponent = entity->GetTransformComponent();
    if (!transformComponent)
    {
        return nullptr;
    }

    glm::vec3 position = transformComponent->GetPosition();
    glm::quat rotation = glm::quat(glm::radians(transformComponent->GetRotation())); // Convert rotation to quaternion
    reactphysics3d::Vector3 rpPosition(position.x, position.y, position.z);
    reactphysics3d::Quaternion rpRotation(rotation.x, rotation.y, rotation.z, rotation.w);
    reactphysics3d::Transform transform(rpPosition, rpRotation);

    return physicsWorld->createRigidBody(transform);
}


