#include "shapes.h"

void Shapes::draw(Shader& shader) {
    shader.useShader();

    if(hasTex) {
        glActiveTexture(GL_TEXTURE0 + texId);
        glBindTexture(GL_TEXTURE_2D, texId);
    }   

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, verticesNum);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Shapes::translate(glm::vec3 position) {
    this->model = glm::translate(this->model, position);
}

void Shapes::scale(glm::vec3 scale) {
    this->model = glm::scale(this->model, scale);
}

void Shapes::rotate(RotationAxis axis, float fator) {
    switch(axis) {
        case Xaxis:
            this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case Yaxis:
            this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Zaxis:
            this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        default:
            errorLog("Warning: Shapes rotate without axis declared!");
    }
}

Cube::Cube(glm::vec3 initialPos, const char* texPath, glm::mat4& model) : model(model), Shapes(initialPos, texPath, model) {
    verticesNum = (sizeof(vertices) / sizeof(float)) / 8;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(1);
	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

    if(texPath != "none") {
        Texture cubeTexture(texPath);
        texId = cubeTexture.getID();
        hasTex = true;
    }

    this->model = glm::translate(this->model, initialPos);
}
