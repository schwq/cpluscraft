#include "Shapes.h"

void Shapes::draw(Shader& shader) {
    shader.useShader();
    glActiveTexture(GL_TEXTURE0);
    shader.setInt("material.texture_diffuse1", 0);
    glBindTexture(GL_TEXTURE_2D, tex.getID());
    shader.setFloat("material.specular", specularFator);

    if(firstTimeRender) {
        position = initialPosition;
        firstTimeRender = false;
    }

    this->model = glm::translate(this->model, position);
    
    if(Xrotation != 0.0f) {
        this->model = glm::rotate(this->model, glm::radians(this->Xrotation), glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if(Yrotation != 0.0f) {
        this->model = glm::rotate(this->model, glm::radians(this->Yrotation), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if(Zrotation != 0.0f) {
        this->model = glm::rotate(this->model, glm::radians(this->Zrotation), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    
    this->model = glm::scale(this->model, scaling);
    
    
    shader.setMat4("model", this->model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, verticesNum);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    // reset model
    this->model = glm::mat4(1.0f);
}

void Shapes::translate(glm::vec3 positionVec) {
    position = positionVec;
}

void Shapes::scale(glm::vec3 scaleVec) {
    scaling = scaleVec;
}

void Shapes::rotate(RotationAxis axis, float fator) {
    switch(axis) {
        case Xaxis:
            Xrotation = fator;
            //this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case Yaxis:
            Yrotation = fator;
            //this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Zaxis:
            Zrotation = fator;
            //this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        default:
            logError("Warning: Shapes rotate without axis declared!");
    }
}

Cube::Cube(glm::vec3 initialPos, Texture& tex, bool isNull) : Shapes(initialPos, tex, isNull) {
    
    if(isNull) {
        return;
    }
    
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
	
    glBindVertexArray(0); 

    this->initialPosition = initialPos;
}
