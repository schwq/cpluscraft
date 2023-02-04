#include "window.h"

Window::Window(GLFWwindow*& window, const char* windowTitle, int width, int heigth) : window(window), windowTitle(windowTitle) {
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	this->window = glfwCreateWindow(width, heigth, this->windowTitle, NULL, NULL);

    if (window == NULL) {
		errorLog("Error: Cannot create GLFW window!");
		glfwTerminate();
	}
}

void Window::checkGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        errorLog("Error: Cannot load GLAD!");
    }
}