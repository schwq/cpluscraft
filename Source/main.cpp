#include "Common.h"
#include "Globals.h"

Window* window = Window::get("Demo", windowWidth, windowHeight);
Camera camera(glm::vec3(1.0f));
PlayerUI* playerUI = PlayerUI::get(window);

void resizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);


int main() {

	glfwMakeContextCurrent(window->returnWindow());
	glfwSetFramebufferSizeCallback(window->returnWindow(), resizeCallback);
	glfwSetInputMode(window->returnWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window->returnWindow(), mouseCallback);
	window->checkGLAD();


	glm::mat4 m1 = glm::mat4(1.0f);
	glm::mat4 m2 = glm::mat4(1.0f);
	glm::vec3 v1 = glm::vec3(2.0f);
	glm::vec3 v2 = glm::vec3(1.0f);

	if(glm::translate(m1, v1) == glm::translate(m2, v2)) logMessage("Equal");

	Game* game = Game::get();
	game->run();
	return game->game_return;
}

void resizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if(cameraShouldMove) {
   		camera.mouseCallback(firstMouse, lastX, lastY, xpos, ypos);
 	}
}