#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "error.h"
#include "callback.h"
#include "objects/shader.h"
#include "player/camera.h"
#include "objects/model.h"
#include "objects/shapes.h"

class Game {

public:

    Game(Camera& camera, GLFWwindow* window);

    void run();
    void terminate() {
        return;
    }

    //~Game();

    int game_return = 0;

private:

    bool lightOn = true;
    glm::vec3 lightPosition;
    void setLightings(Shader& shader);

    Camera& camera;
    GLFWwindow* window;
    Shader lightShader = Shader(currentOSPath("\\source\\resources\\shaders\\lightingVertex.glsl", "/resources/shaders/lightingVertex.glsl").c_str(),
		currentOSPath("\\source\\resources\\shaders\\lightingFragment.glsl", "/resources/shaders/lightingFragment.glsl").c_str(), "Light Shader");
    Shader defaultShader = Shader(currentOSPath("\\source\\resources\\shaders\\defaultVertex.glsl", "/resources/shaders/defaultVertex.glsl").c_str(),
		currentOSPath("\\source\\resources\\shaders\\defaultFragment.glsl", "/resources/shaders/defaultFragment.glsl").c_str(), "Main Shader");

    glm::vec3 pointLightPositions[4] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
    };


};

#endif