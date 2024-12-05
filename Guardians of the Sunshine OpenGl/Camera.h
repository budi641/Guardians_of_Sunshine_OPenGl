#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

enum class ProjectionType {
    Perspective,
    Orthographic
};

class Camera {

private:
    glm::vec3 position = {};   
    float pitch = 0.0f, yaw = 0.0f;  
    float fovy = 1.5f;               
    float near = 0.01f, far = 100.0f; 
    float orthoHeight = 10.0f;       
    float zoom = 1.0f;             

    ProjectionType projectionType = ProjectionType::Perspective; 

    float moveSpeed = 0.1f; 
    float rotateSpeed = 0.05f;

public:

    
    Camera();

    float get_move_speed();
    float get_rotate_speed();
    void set_move_speed(float new_move_speed);
    void get_rotate_speed(float new_rotate_speed);
        
    
    glm::vec3 get_position() const;
    void set_position(const glm::vec3& newPosition);

   
    float get_pitch() const;
    void set_pitch(float newPitch);

    
    float get_yaw() const;
    void set_yaw(float newYaw);

    void set_fovy(float newFovy);
    float get_fovy() const;

    void set_zoom(float newZoom);
    float get_zoom() const;


    void set_ortho_height(float height);
    float get_ortho_hight();
    
    glm::vec3 get_forward() const;

    
    glm::vec3 get_right() const;

   //
    glm::mat4 get_view_matrix() const;

    
    glm::mat4 get_projection_matrix(int width, int height) const;

    
    void move_forward(float deltaTime);

   
    void move_right(float deltaTime);

    
    void move_up(float deltaTime);

    void move_backward(float deltaTime);


    void move_left(float deltaTime);


    void move_down(float deltaTime);

    
    void zoom_in(float deltaTime);
    void zoom_out(float deltaTime);


    void rotate(float deltaX, float deltaY);

    
    void toggle_projection();

    
    void set_clipping_planes(float nearPlane, float farPlane);

    




};


