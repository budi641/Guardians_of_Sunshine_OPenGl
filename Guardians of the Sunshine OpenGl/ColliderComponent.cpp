#include "ColliderComponent.h"
#include "Entity.h"
#include "World.h"
#include "PhysicsManager.h"
#include "StaticMeshComponent.h"


ColliderComponent::ColliderComponent()
{
    colliderShape = ColliderShape::ConvexMesh;
}

ColliderComponent::ColliderComponent(float x, float y, float z)
{

	this->size = reactphysics3d::Vector3(x/2,y/2,z/2);

	colliderShape = ColliderShape::Box;
}

ColliderComponent::ColliderComponent(float radius)
{
	this->radius = radius;
	colliderShape = ColliderShape::Sphere;
}

ColliderComponent::ColliderComponent(float radius, float height)
{
	this->radius = radius;
	this->height = height;
	colliderShape = ColliderShape::Capsule;
}

ColliderComponent::~ColliderComponent()
{
	delete collider;
	delete rigidBody;

}

void ColliderComponent::Update(float deltaTime)
{
	
	if (rigidBody)
	{
		reactphysics3d::Transform transform = rigidBody->getTransform();
		parent->GetTransformComponent()->UpdatePhysicsTransform(transform);
	}

    if (parent->world->physicsHandler->physicsWorld)
    {
        parent->world->physicsHandler->physicsWorld->setEventListener(collison);
    }
}

void ColliderComponent::OnAdd()
{
	rigidBody = parent->world->physicsHandler->CreateRigidBody(parent);

    rigidBody->setIsDebugEnabled(true);

	reactphysics3d::Transform transform = parent->GetEntityPhysicsTransform();

    StaticMeshComponent* mesh = parent->GetComponentByClass<StaticMeshComponent>();

    collison = new CustomCollisionListener(parent);

	switch (colliderShape)
	{
		case ColliderShape::Box:

			 collider = rigidBody->addCollider(parent->world->physicsHandler->physicsCommon->createBoxShape(size), transform);

		case ColliderShape::Sphere:

			collider = rigidBody->addCollider(parent->world->physicsHandler->physicsCommon->createSphereShape(radius), transform);

		case ColliderShape::Capsule:

			collider = rigidBody->addCollider(parent->world->physicsHandler->physicsCommon->createCapsuleShape(radius, height), transform);
		
		case ColliderShape::ConvexMesh:



            if (mesh)
            {
               // collider = rigidBody->addCollider(CreateConvexMeshShape(mesh->GetVertices(), mesh->GetIndices()), transform);
            }

		
		default:

			return;
	}


}

void ColliderComponent::Serialize(nlohmann::json& jsonData) const
{
}

void ColliderComponent::Deserialize(const nlohmann::json& jsonData)
{
}

reactphysics3d::ConvexMeshShape* ColliderComponent::CreateConvexMeshShape(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
  

    // Ensure vertices and indices are valid
    if (vertices.empty() || indices.empty()) {
        std::cerr << "Error: Vertices or indices are empty!" << std::endl;
        return nullptr;
    }

    // Extract vertex positions into a float array
    size_t vertexCount = vertices.size();
    std::vector<float> vertexPositions;
    vertexPositions.reserve(vertexCount * 3);
    for (const auto& vertex : vertices) {
        vertexPositions.push_back(vertex.position.x);
        vertexPositions.push_back(vertex.position.y);
        vertexPositions.push_back(vertex.position.z);
    }

    // Convert indices to int
    std::vector<int> physicsIndices(indices.begin(), indices.end());

    // Define polygon faces (assuming quads: 4 indices per face)
    size_t faceCount = indices.size() / 4;
    std::vector<reactphysics3d::PolygonVertexArray::PolygonFace> polygonFaces(faceCount);
    for (size_t f = 0; f < faceCount; ++f) {
        polygonFaces[f].indexBase = f * 4;
        polygonFaces[f].nbVertices = 4; // Each face is a quad
    }

    // Create the PolygonVertexArray
    auto* polygonVertexArray = new reactphysics3d::PolygonVertexArray(
        vertexCount,
        vertexPositions.data(),
        3 * sizeof(float),
        physicsIndices.data(),
        sizeof(int),
        faceCount,
        polygonFaces.data(),
        reactphysics3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
        reactphysics3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE
    );

    // Create the ConvexMesh
    std::vector<reactphysics3d::Message> messages;

    reactphysics3d::ConvexMesh* convexMesh = parent->world->physicsHandler->physicsCommon->createConvexMesh(*polygonVertexArray, messages);

    // Display messages (info, warning, error)
    for (const auto& message : messages) {
        std::string messageType;
        switch (message.type) {
        case reactphysics3d::Message::Type::Information:
            messageType = "info";
            break;
        case reactphysics3d::Message::Type::Warning:
            messageType = "warning";
            break;
        case reactphysics3d::Message::Type::Error:
            messageType = "error";
            break;
        }
        std::cerr << "Message (" << messageType << "): " << message.text << std::endl;
    }

    if (!convexMesh) {
        std::cerr << "Failed to create ConvexMesh!" << std::endl;
        delete polygonVertexArray;
        return nullptr;
    }

    // Create the ConvexMeshShape
    reactphysics3d::ConvexMeshShape* convexMeshShape = parent->world->physicsHandler->physicsCommon->createConvexMeshShape(convexMesh);

    // Clean up
    delete polygonVertexArray;

    return convexMeshShape;
}

