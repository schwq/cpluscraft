#include "Game.h"
#include "Physics/BlockCollision.h"

Game* Game::get() {
	static Game* rt_game = new Game();
	return rt_game;
}

Game::Game() {
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	logMessage("Info: Maximum of texture units: ",  GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	logMessage("Info: Maximum texture size: ", GL_MAX_TEXTURE_SIZE);
}

void Game::run() {
	
	MusicBuffer gameMusic(searchMusic("ambience01.wav").c_str());

	std::vector<std::string> skybox = {
		searchTexture("tex_Skybox/right.jpg"),
		searchTexture("tex_Skybox/left.jpg"),
		searchTexture("tex_Skybox/top.jpg"),
		searchTexture("tex_Skybox/bottom.jpg"),
		searchTexture("tex_Skybox/front.jpg"),
		searchTexture("tex_Skybox/back.jpg")
	};

	playerUI->start();

	Texture necoTex(searchTexture("lamp.png").c_str());
	Texture stone(searchTexture("stone.png").c_str());
	Texture brick(searchTexture("brick.png").c_str());
	Texture glass(searchTexture("glass.png").c_str());
	Texture skyboxTex(skybox);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);
	glm::mat4 model = glm::mat4(1.0f);
	
	Skybox mainSkybox(skybox, skyboxShader, skyboxTex);
	gameMusic.play();
	Block grass(brick, NSdefaultShader, "Grass Block");
	Block test(stone, NSdefaultShader, "Stone Block");
	Cube cb01(glm::vec3(1.0f), brick);

	for(uint x = 0; x < gl_Blocks.size(); x++) {
		logMessage(gl_Blocks.at(x).getName());
	}

	while (!glfwWindowShouldClose(window->returnWindow())) {

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		gameMusic.updateBufferStream();

		grass.translate(glm::vec3(1.0f, 0.0f, 0.0f));
		test.translate(glm::vec3(1.0f, 0.0f, 1.0f));
		checkOverLapFaces();

		processInput(window->returnWindow(), deltaTime);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultShader.useShader();
		defaultShader.setVec3("lightPosition", glm::vec3(1.0f));
		defaultShader.setVec3("viewerPos", camera.getPosition());
		defaultShader.setFloat("material.shininess", 32.0f);
		defaultShader.setMat4("projection", projection);
		camera.update(defaultShader); // set viewer position
		defaultShader.manifestShaderProperties(camera);
		
		NSdefaultShader.useShader();
		NSdefaultShader.setVec3("lightPosition", glm::vec3(1.0f));
		NSdefaultShader.setVec3("viewerPos", camera.getPosition());
		NSdefaultShader.setFloat("material.shininess", 32.0f);
		NSdefaultShader.setMat4("projection", projection);
		camera.update(NSdefaultShader); // set viewer position
		NSdefaultShader.manifestShaderProperties(camera);

		
		grass.draw();
		test.draw();

		lightShader.useShader();
		lightShader.setMat4("projection", projection);
		lightShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		camera.update(lightShader);
		mainSkybox.draw(glm::mat4(glm::mat3(camera.returnViewMatrix())), projection);
		
		model = glm::translate(model, glm::vec3(1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		lightShader.setMat4("model", model);
		playerUI->render();

		glfwSwapBuffers(window->returnWindow());
		glfwPollEvents();
	}

	playerUI->terminate();
	glfwTerminate();
    if(!terminate(EXIT_SUCCESS)) { return; }
}

