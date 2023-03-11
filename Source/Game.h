#ifndef _GAME_H_
#define _GAME_H_

#include "Common.h"
#include "LogSystem.h"
#include "Objects/Shader.h"
#include "Player/Camera.h"
#include "Objects/Model.h"
#include "Objects/Shapes.h"
#include "Player/PlayerUI.h"
#include "Editor/Window.h"
#include "World/Skybox.h"
#include "Audio/MusicBuffer.h"
#include "Audio/SoundDevices.h"
#include "World/TerrainGenerator.h"
#include "Objects/Blocks/Blocks.h"
#include "Globals.h"

class Game {

public:

    static Game* get();
    void run();
    bool terminate(int EXIT) {
        game_return = EXIT;
        return EXIT == 0;
    }

    int game_return = 0;

private:

    Game();

    bool lightOn = true;
    SoundDevices* soundDevices = SoundDevices::get();
    Shader lightShader = Shader(searchShader("Lighting/lightingVertex.glsl").c_str(), searchShader("Lighting/lightingFragment.glsl").c_str(), "Light Shader");
    Shader defaultShader = Shader(searchShader("Objects/SpecularTexture/defaultVertex.glsl").c_str(), searchShader("Objects/SpecularTexture/defaultFragment.glsl").c_str(), "Main Shader");
    Shader NSdefaultShader = Shader(searchShader("Objects/NoSpecularTexture/defaultVertexNS.glsl").c_str(), searchShader("Objects/NoSpecularTexture/defaultFragmentNS.glsl").c_str(), "NSMain Shader");
    Shader skyboxShader = Shader(searchShader("Skybox/skyboxVertex.glsl").c_str(), searchShader("Skybox/skyboxFragment.glsl").c_str(), "Skybox Shader");
};

#endif  