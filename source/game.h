#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "error.h"
#include "callback.h"
#include "objects/shader.h"
#include "player/camera.h"
#include "objects/model.h"
#include "objects/shapes.h"
#include "player/playerUI.h"
#include "editor/window.h"
#include "world/skybox.h"
#include "audio/musicBuffer.h"
#include "audio/soundDevices.h"
#include "world/terrain.h"

class Game {

public:

    Game(Camera& camera, GLFWwindow* window, Window*& windowControl);

    void run();
    void terminate(int EXIT) {
        game_return = EXIT;
        exit(-1);
    }

    //~Game();

    int game_return = 0;

private:

    bool lightOn = true;
    Window*& windowControl;
    Camera& camera;
    GLFWwindow* window;
    Shader lightShader = Shader(searchShader("lighting/lightingVertex.glsl").c_str(), searchShader("lighting/lightingFragment.glsl").c_str(), "Light Shader");
    Shader defaultShader = Shader(searchShader("objects/specularTexture/defaultVertex.glsl").c_str(), searchShader("objects/specularTexture/defaultFragment.glsl").c_str(), "Main Shader");
    Shader NSdefaultShader = Shader(searchShader("objects/noSpecularTexture/defaultVertexNS.glsl").c_str(), searchShader("objects/noSpecularTexture/defaultFragmentNS.glsl").c_str(), "NSMain Shader");
    Shader skyboxShader = Shader(searchShader("skybox/skyboxVertex.glsl").c_str(), searchShader("skybox/skyboxFragment.glsl").c_str(), "Skybox Shader");
    Shader CMdefaultShader = Shader(searchShader("Cubemap/defaultVertexCM.glsl").c_str(), searchShader("Cubemap/defaultFragmentCM.glsl").c_str(), "CubeMap Shader");
};

#endif