#include "game.h"

Game::Game(Camera& camera, GLFWwindow* window) : camera(camera), window(window) {
    glEnable(GL_DEPTH_TEST);
	msgLog("Maximum of texture units: ",  GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	msgLog("Maximum texture size: ", GL_MAX_TEXTURE_SIZE);
    lightPosition = glm::vec3(1.0f);
}

void Game::run() {
    Model customModel(currentOSPath("\\source\\resources\\models\\backpack\\backpack.obj", "/resources/models/backpack/backpack.obj"));

	glm::mat4 model = glm::mat4(1.0f);

	Cube cube1(glm::vec3(1.0f, 1.0f, 1.0f), "none", model);

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
	
		defaultShader.useShader();
		defaultShader.setVec3("lightPosition", lightPosition);
		defaultShader.setVec3("viewerPos", camera.getPosition());
		defaultShader.setFloat("material.shininess", 32.0f);
		defaultShader.setMat4("projection", projection);
		camera.update(defaultShader); // set viewer position
		setLightings(defaultShader);
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat, glm::vec3(10.0f, 10.0f, 10.0f));
		modelMat = glm::scale(modelMat, glm::vec3(0.5f));
		defaultShader.setMat4("model", modelMat);
		customModel.draw(defaultShader);

		lightShader.useShader();
		lightShader.setMat4("projection", projection);
		lightShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		camera.update(lightShader);
		cube1.draw(lightShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPosition);
		model = glm::scale(model, glm::vec3(0.1f));
		lightShader.setMat4("model", model);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
    terminate();
}
void Game::setLightings(Shader& shader) {
    shader.setVec3("source_dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader.setVec3("source_dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setVec3("source_dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader.setVec3("source_dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	
	// point light 1
	shader.setVec3("source_ptrLight[0].position", pointLightPositions[0]);
	shader.setVec3("source_ptrLight[0].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("source_ptrLight[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[0].constant", 1.0f);
	shader.setFloat("source_ptrLight[0].linear", 0.09f);
	shader.setFloat("source_ptrLight[0].quadratic", 0.032f);
	// point light 2
	shader.setVec3("source_ptrLight[1].position", pointLightPositions[1]);
	shader.setVec3("source_ptrLight[1].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("source_ptrLight[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[1].constant", 1.0f);
	shader.setFloat("source_ptrLight[1].linear", 0.09f);
	shader.setFloat("source_ptrLight[1].quadratic", 0.032f);
	// point light 3
	shader.setVec3("source_ptrLight[2].position", pointLightPositions[2]);
	shader.setVec3("source_ptrLight[2].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("source_ptrLight[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[2].constant", 1.0f);
	shader.setFloat("source_ptrLight[2].linear", 0.09f);
	shader.setFloat("source_ptrLight[2].quadratic", 0.032f);
	// point light 4
	shader.setVec3("source_ptrLight[3].position", pointLightPositions[3]);
	shader.setVec3("source_ptrLight[3].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("source_ptrLight[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_ptrLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_ptrLight[3].constant", 1.0f);
	shader.setFloat("source_ptrLight[3].linear", 0.09f);
	shader.setFloat("source_ptrLight[3].quadratic", 0.032f);
	
	// source_sptLight
	shader.setVec3("source_sptLight.position", camera.getPosition());
	shader.setVec3("source_sptLight.direction", camera.getDirection());
	shader.setVec3("source_sptLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setVec3("source_sptLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("source_sptLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_sptLight.constant", 1.0f);
	shader.setFloat("source_sptLight.linear", 0.09f);
	shader.setFloat("source_sptLight.quadratic", 0.032f);
	shader.setFloat("source_sptLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("source_sptLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	
	shader.setVec3("source_cbLight.position", lightPosition); 
	shader.setVec3("source_cbLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("source_cbLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	shader.setVec3("source_cbLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("source_cbLight.constant", 1.0f);
	shader.setFloat("source_cbLight.linear", 0.09f);
	shader.setFloat("source_cbLight.quadratic", 0.032f);
}