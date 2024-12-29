#include "RenderManager.h"
#include <iostream>
#include"PhysicsManager.h"

void RenderManager::SetupQuad()
{
    if (quadVAO == 0) {
        GLfloat vertices[] = {

            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f, 
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 
             1.0f, -1.0f, 0.0f,   1.0f, 0.0f,  

            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  
             1.0f, -1.0f, 0.0f,   1.0f, 0.0f,  
             1.0f,  1.0f, 0.0f,   1.0f, 1.0f   
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
    }
}

RenderManager::RenderManager(int width, int height, const char* windowTitle)
    : width(width), height(height) {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        throw std::runtime_error("GLFW initialization failed");
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        throw std::runtime_error("GLFW window creation failed");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("GLAD initialization failed");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0,10* width, 10*height);
        });

    SetUpOpenGL();
    camera = new Camera(CameraType::Perspective, width, height);

    SetUpPostProcessing();
}

RenderManager::~RenderManager() {
    delete skybox;
    delete camera;
    delete shader;

    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}


void RenderManager::AddLight(const Light& light) {
    lights.push_back(light);
}
void RenderManager::SetUpOpenGL() {
    if (enableDepthTest) {
        glEnable(GL_DEPTH_TEST);

    }

    if (enableBackFaceCulling) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
}

void RenderManager::Render(World* world) 
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (skybox && camera) {
        skybox->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
    }

    if (shader) {
        shader->Bind();
    }

    SendLightsToShader();
    world->RenderWorld(this);
    world->physicsHandler->UpdateDebugRendering(this);

    if (postProcessShader)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        postProcessShader->Bind();
        postProcessShader->SetUniform("screenTexture", 0);
        postProcessShader->SetUniform("u_resolution", glm::vec2(width, height));
        float time = glfwGetTime();
        postProcessShader->SetUniform("u_time", time);

   
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void RenderManager::SetDepthTest(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
    enableDepthTest = enable;
}

void RenderManager::SetBackFaceCulling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
    enableBackFaceCulling = enable;
}

void RenderManager::SendLightsToShader() {
    const int MAX_LIGHTS = 10;

    int numLights = lights.size();

    shader->SetUniform("numLights", numLights);

    for (int i = 0; i < std::min<int>(lights.size(), MAX_LIGHTS); ++i) {
        std::string lightName = "lights[" + std::to_string(i) + "]";

        shader->SetUniform(lightName + ".color", lights[i].color);
        shader->SetUniform(lightName + ".intensity", lights[i].intensity);
        shader->SetUniform(lightName + ".range", lights[i].range);
        shader->SetUniform(lightName + ".cutoff", lights[i].cutoff);
        shader->SetUniform(lightName + ".outerCutoff", lights[i].outerCutoff);
        shader->SetUniform(lightName + ".type", static_cast<int>(lights[i].type));

        if (lights[i].type == LightType::Directional) {
            shader->SetUniform(lightName + ".direction", lights[i].direction);
        }
        else if (lights[i].type == LightType::Point || lights[i].type == LightType::Spotlight) {
            shader->SetUniform(lightName + ".position", lights[i].position);
            shader->SetUniform(lightName + ".direction", lights[i].direction);
        }
    }
}

void RenderManager::SetUpPostProcessing()
{
    SetupQuad();

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer not complete!" << std::endl;
        throw std::runtime_error("Framebuffer setup failed");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 

 
}
