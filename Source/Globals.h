#ifndef _GLOBAL_H_
#define _GLOBAL_H_

class Game;
class Window;
class PlayerUI;
class Camera;

#include "Common.h"
#include "LogSystem.h"
#include "Editor/Window.h"
#include "Player/Camera.h"
#include "Player/PlayerUI.h"
#include "Game.h"
#include "Objects/Blocks/Blocks.h"

extern Window* window;
extern PlayerUI* playerUI;
extern Camera camera;

extern uint windowWidth;
extern uint windowHeight;
extern bool cameraShouldMove;
extern bool freeCursor;
extern bool firstMouse;
extern float lastX;
extern float lastY;

extern std::vector<Block> gl_Blocks;

static void processInput(GLFWwindow* window, float delta) {
    static uint timerControl = 0;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.updatePosition(Camera_Forward,delta);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.updatePosition(Camera_Right, delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.updatePosition(Camera_Backward, delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.updatePosition(Camera_Left, delta);
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        timerControl++;

        if(timerControl > 3) {
            if(freeCursor) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                freeCursor = false;
                cameraShouldMove = true;
            } else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                freeCursor = true;
                cameraShouldMove = false;
            }

            timerControl = 0;

        }
    }
}


#endif