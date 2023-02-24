#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "common.h"
#include "error.h"
#include "player/camera.h"

extern Camera camera;
extern bool freeCursor;
extern bool cameraShouldMove;

static void processInput(GLFWwindow* window, float delta) {
    
	static unsigned int timerControl = 0;

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