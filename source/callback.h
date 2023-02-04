#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "common.h"
#include "error.h"
#include "player/camera.h"

extern Camera camera;

static void processInput(GLFWwindow* window, float delta) {
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.updatePosition(Camera_Forward,delta);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.updatePosition(Camera_Right, delta);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.updatePosition(Camera_Backward, delta);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.updatePosition(Camera_Left, delta);

}

#endif