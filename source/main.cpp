#include "game.h"
#include "callback.h"
#include "editor/window.h"

int windowWidth = 1200;
int windowHeight = 800;
float lastX = static_cast<float>(windowWidth / 2);
float lastY = static_cast<float>(windowHeight / 2);
bool firstMouse = true;
bool freeCursor = false;
bool cameraShouldMove = true;

GLFWwindow* window;
Camera camera = Camera(glm::vec3(1.0f, 1.0f, 1.0f));

static void resizeCallback(GLFWwindow* window, int width, int height);
static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

int main() {
	
	Window* windowSystem = Window::get(window, "demo", windowWidth, windowHeight);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

	windowSystem->checkGLAD();

	Game game(camera, window, windowSystem);
	game.run();

	return game.game_return;
}

void resizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if(cameraShouldMove) {
   		camera.mouseCallback(firstMouse, lastX, lastY, xpos, ypos);
 	}
}