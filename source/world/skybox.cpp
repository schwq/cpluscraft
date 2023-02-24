#include "skybox.h"

 Skybox::Skybox(std::vector<std::string> paths, Shader& shader, Texture& texture, unsigned int format) : shader(shader), texture(texture) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	glBindVertexArray(0); 
    Texture skyboxTex(paths);
    texture = skyboxTex;
 }

void Skybox::draw(glm::mat4 view, glm::mat4 projection) {
    glDepthFunc(GL_LEQUAL);
	shader.useShader();
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
    glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture.getID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}