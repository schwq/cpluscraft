#include "common.h"
#include "error.h"
#include "shader.h"
#include "camera.h"
#include "model.h"

static int windowWidth = 1200;
static int windowHeight = 800;

float lastX = static_cast<float>(windowWidth / 2);
float lastY = static_cast<float>(windowHeight / 2);

bool firstMouse = true;
bool lightOn = true;

static void resizeCallback(GLFWwindow* window, int width, int height);
static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
static void processInput(GLFWwindow* window, float delta);
static void setLightings(Shader& shader);
glm::vec3 lightPosition(1.0f);
Camera mainCamera;

glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
};

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Demo", NULL, NULL);

	if (window == NULL) {
		errorLog("Error: Cannot create GLFW window!");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		errorLog("Error: Cannot load GLAD!");
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader mainShader(currentOSPath("\\source\\shaders\\defaultVertex.glsl", "/source/shaders/defaultVertex.glsl").c_str(),
		currentOSPath("\\source\\shaders\\defaultFragment.glsl", "/source/shaders/defaultFragment.glsl").c_str(), "Main Shader");
	Shader lightShader(currentOSPath("\\source\\shaders\\lightingVertex.glsl", "/source/shaders/lightingVertex.glsl").c_str(),
		currentOSPath("\\source\\shaders\\lightingFragment.glsl", "/source/shaders/lightingFragment.glsl").c_str(), "Light Shader");
	
	Model model(currentOSPath("\\source\\models\\backpack\\backpack.obj", "/source/shaders/lightingVertex.glsl"));

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window, deltaTime);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		mainShader.useShader();
		mainShader.setVec3("lightPosition", lightPosition);
		mainShader.setVec3("viewerPos", mainCamera.getPosition());
		/*
		mainShader.setVec3("material.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		mainShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		mainShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		*/
		mainShader.setFloat("material.shininess", 32.0f);
		mainShader.setMat4("projection", projection);
		mainCamera.update(mainShader); // set viewer position

		setLightings(mainShader);

		model.draw(mainShader);

		lightShader.useShader();
		lightShader.setMat4("projection", projection);
		lightShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		mainCamera.update(lightShader);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPosition);
		model = glm::scale(model, glm::vec3(0.5f));
		lightShader.setMat4("model", model);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}

static void resizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window, float delta) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) mainCamera.updatePosition(Camera_Forward,delta);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) mainCamera.updatePosition(Camera_Right, delta);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) mainCamera.updatePosition(Camera_Backward, delta);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) mainCamera.updatePosition(Camera_Left, delta);
}

static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}

	float yoffset = lastY - static_cast<float>(ypos);
	float xoffset = static_cast<float>(xpos) - lastX;
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	mainCamera.updateDirection(xoffset, yoffset);
}

static void setLightings(Shader& shader) {
	shader.setVec3("source_dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader.setVec3("source_dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("source_dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader.setVec3("source_dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	// point light 1
	shader.setVec3("source_ptrLight[0].position", pointLightPositions[0]);
	shader.setVec3("source_ptrLight[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("source_ptrLight[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[0].constant", 1.0f);
	shader.setFloat("source_ptrLight[0].linear", 0.09f);
	shader.setFloat("source_ptrLight[0].quadratic", 0.032f);
	// point light 2
	shader.setVec3("source_ptrLight[1].position", pointLightPositions[1]);
	shader.setVec3("source_ptrLight[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("source_ptrLight[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[1].constant", 1.0f);
	shader.setFloat("source_ptrLight[1].linear", 0.09f);
	shader.setFloat("source_ptrLight[1].quadratic", 0.032f);
	// point light 3
	shader.setVec3("source_ptrLight[2].position", pointLightPositions[2]);
	shader.setVec3("source_ptrLight[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("source_ptrLight[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[2].constant", 1.0f);
	shader.setFloat("source_ptrLight[2].linear", 0.09f);
	shader.setFloat("source_ptrLight[2].quadratic", 0.032f);
	// point light 4
	shader.setVec3("source_ptrLight[3].position", pointLightPositions[3]);
	shader.setVec3("source_ptrLight[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("source_ptrLight[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[3].constant", 1.0f);
	shader.setFloat("source_ptrLight[3].linear", 0.09f);
	shader.setFloat("source_ptrLight[3].quadratic", 0.032f);
	// source_sptLight
	shader.setVec3("source_sptLight.position", mainCamera.getPosition());
	shader.setVec3("source_sptLight.direction", mainCamera.getDirection());
	shader.setVec3("source_sptLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("source_sptLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("source_sptLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_sptLight.constant", 1.0f);
	shader.setFloat("source_sptLight.linear", 0.09f);
	shader.setFloat("source_sptLight.quadratic", 0.032f);
	shader.setFloat("source_sptLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("source_sptLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	shader.setVec3("source_cbLight.position", lightPosition); 
	shader.setVec3("source_cbLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("source_cbLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_cbLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_cbLight.constant", 1.0f);
	shader.setFloat("source_cbLight.linear", 0.09f);
	shader.setFloat("source_cbLight.quadratic", 0.032f);
	
}