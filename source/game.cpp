#include "game.h"

Game::Game(Camera& camera, GLFWwindow* window, Window*& windowControl) : camera(camera), window(window), windowControl(windowControl) {
    glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	logMessage("Info: Maximum of texture units: ",  GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	logMessage("Info: Maximum texture size: ", GL_MAX_TEXTURE_SIZE);
}

void Game::run() {

	SoundDevices* soundDevices = SoundDevices::get();
	MusicBuffer ost01(searchMusic("ost01.wav").c_str());

	std::vector<std::string> skybox = {
		searchTexture("skyboxTex/right.jpg"),
		searchTexture("skyboxTex/left.jpg"),
		searchTexture("skyboxTex/top.jpg"),
		searchTexture("skyboxTex/bottom.jpg"),
		searchTexture("skyboxTex/front.jpg"),
		searchTexture("skyboxTex/back.jpg")
	};

	std::vector<std::string> dirt = {
		searchTexture("dirt/side.jpg"),
		searchTexture("dirt/side.jpg"),
		searchTexture("dirt/top.jpg"),
		searchTexture("dirt/under.jpg"),
		searchTexture("dirt/side.jpg"),
		searchTexture("dirt/side.jpg")
	};

	PlayerUI* playerUI = PlayerUI::get(windowControl);
	playerUI->start();
	Model gun(searchModel("gun/untitled.obj"));
    //Model customModel(searchModel("backpack/backpack.obj"));
	//Model sword(searchModel("sword/untitled.obj"));

	Texture necoTex(searchTexture("lamp.png").c_str());
	Texture stone(searchTexture("stone.png").c_str());
	Texture brick(searchTexture("brick.png").c_str());
	Texture glass(searchTexture("glass.png").c_str());
	Texture skyboxTex(skybox);
	Texture dirtTex(dirt);
	Cube cube1(glm::vec3(1.0f, 1.0f, 1.0f), brick);
	Cube cube2(glm::vec3(10.0f, 10.0f, 10.0f), stone);
	Cube cube3(glm::vec3(1.0f), necoTex);
	Cube cube4(glm::vec3(1.0f), glass);
	Cube cube5(glm::vec3(1.0f), dirtTex);

	Terrain stoneTerrain(cube2, playerUI->fatorXterrain, 1, playerUI->fatorZterrain);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

	glm::mat4 model = glm::mat4(1.0f);
	Skybox mainSkybox(skybox, skyboxShader, skyboxTex);

	ost01.play();

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ost01.updateBufferStream();

		processInput(window, deltaTime);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		defaultShader.useShader();
		defaultShader.setVec3("lightPosition", glm::vec3(1.0f));
		defaultShader.setVec3("viewerPos", camera.getPosition());
		defaultShader.setFloat("material.shininess", 32.0f);
		defaultShader.setMat4("projection", projection);
		camera.update(defaultShader); // set viewer position
		defaultShader.manifestShaderProperties(camera);
		//customModel.translate(glm::vec3(5.0f, 5.0f, 5.0f));
		//customModel.scale(glm::vec3(2.0f));
		//customModel.draw(defaultShader);
		//sword.scale(glm::vec3(0.05f));
		//sword.translate(glm::vec3(10.0f, 10.0f, 10.0f));
		//sword.draw(defaultShader);
		
		NSdefaultShader.useShader();
		NSdefaultShader.setVec3("lightPosition", glm::vec3(1.0f));
		NSdefaultShader.setVec3("viewerPos", camera.getPosition());
		NSdefaultShader.setFloat("material.shininess", 32.0f);
		NSdefaultShader.setMat4("projection", projection);
		camera.update(NSdefaultShader); // set viewer position
		NSdefaultShader.manifestShaderProperties(camera);
		gun.translate(glm::vec3(3.0f));
		gun.draw(NSdefaultShader);
		
		/* cube1.translate(glm::vec3(0.0f, 0.0f, 0.0f));
		cube1.draw(NSdefaultShader);
		cube1.translate(glm::vec3(0.0f, 2.0f, 0.0f));
		cube1.draw(NSdefaultShader);
	
		cube2.translate(glm::vec3(0.0f, 0.0f, 1.0f));
		cube2.draw(NSdefaultShader);

		cube3.translate(glm::vec3(0.0f, 1.0f, 1.0f));
		cube3.draw(NSdefaultShader);

		cube4.translate(glm::vec3(1.0f, 1.0f, 1.0f));
		cube4.draw(NSdefaultShader); */

		stoneTerrain.update(playerUI->fatorXterrain, 1.0f, playerUI->fatorZterrain);
		stoneTerrain.draw(NSdefaultShader);

		CMdefaultShader.useShader();
		CMdefaultShader.setVec3("lightPosition", glm::vec3(1.0f));
		CMdefaultShader.setVec3("viewerPos", camera.getPosition());
		CMdefaultShader.setFloat("material.shininess", 32.0f);
		CMdefaultShader.setMat4("projection", projection);
		camera.update(CMdefaultShader); // set viewer position
		CMdefaultShader.manifestShaderProperties(camera);

		cube5.translate(glm::vec3(3.0f, 0.0f, 0.0f));
		cube5.draw(CMdefaultShader);


		//stoneTerrain.draw(NSdefaultShader);
		
		lightShader.useShader();
		lightShader.setMat4("projection", projection);
		lightShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		camera.update(lightShader);

		mainSkybox.draw(glm::mat4(glm::mat3(camera.returnViewMatrix())), projection);
		
		model = glm::translate(model, glm::vec3(1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		lightShader.setMat4("model", model);

	

		playerUI->render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	playerUI->terminate();
	glfwTerminate();
    terminate(EXIT_SUCCESS);
}