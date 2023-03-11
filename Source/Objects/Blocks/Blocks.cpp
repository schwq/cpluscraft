#include "Blocks.h"
#include "../Shapes.h"
//#include "../../GLfunc/GLfunc.h"
#include "../../Globals.h"

uint Face::ID = 0;
uint Block::countID = 0;

std::string FaceOrientationToString(FaceOrientation orientation) {
    switch(orientation) {
        case Top:
        return "Top";
        break;
        case Bottom:
        return "Bottom";
        break;
        case Right:
        return "Right";
        break;
        case Left:
        return "Left";
        break;
        case Front:
        return "Front";
        break;
        case Back:
        return "Back";
        break;

    }
}


Face::Face(Texture& texture, Shader& shader, Block& parentBlock, FaceOrientation orientation) : texture(texture), shader(shader), parentBlock(parentBlock), orientation(orientation) {
    this->faceID = ID++;
    verticesNum = (sizeof(topVertices) / sizeof(GLfloat)) / 8;

    switch(orientation) {
        case Top:

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(topVertices), topVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0);
        
        break;

        case Bottom:
           
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bottomVertices), bottomVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); 

        break;

        case Back:

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(backVertices), backVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); 

        break;

        case Right:

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rightVertices), rightVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); 

        break;

        case Left:

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(leftVertices), leftVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); 

        break;

        case Front:

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(frontVertices), frontVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); 

        break;

        default:

        logError("Error: Cannot find enum for block orientation!");
        break;
    };

    logMessage("Success: Face ", ID, " created successfully! Parent Block: ", parentBlock.getName(), ", ID: ", parentBlock.getID());
}

void Face::setTexture() {
    shader.useShader();
    glActiveTexture(GL_TEXTURE0);
    shader.setInt("material.texture_diffuse1", 0);
    glBindTexture(GL_TEXTURE_2D, texture.getID());
    shader.setFloat("material.specular", 0.5f);
}

void Face::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, verticesNum);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

Block::Block(Texture& texture, Shader& shader, std::string name,glm::vec3 initialPos) : texture(texture), shader(shader) {
    for(uint x = 0; x < 6; x++) {
        faces.push_back(Face(texture, shader, *this, static_cast<FaceOrientation>(x)));
    }
    ID = countID++;
    
    if(name == LITERAL_NULL) {
        name = "Block" + ID;
    } else {
        this->name = name;
    }

    gl_Blocks.push_back(*this);
}

void Block::translate(glm::vec3 value) {
    position = value;
}

void Block::rotate(RotationAxis axis, float value) {
    switch(axis) {
        case Xaxis:
            rotationX = value;
            //this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case Yaxis:
            rotationY = value;
            //this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case Zaxis:
            rotationZ = value;
            //this->model = glm::rotate(this->model, glm::radians(fator), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        default:
            logError("Warning: Shapes rotate without axis declared!");
    }
}

 void Block::scale(float value) {
    scaleFator = value;
}

void Block::draw() {

        for(uint x = 0; x < 6; x++) {
            if(faces.at(x).getShouldDraw()) {
                faces.at(x).setTexture();

                modelMatrix = glm::translate(modelMatrix, position);
                
                if(rotationX != 0.0f) {
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
                }
                if(rotationY != 0.0f) {
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
                }
                if(rotationZ != 0.0f) {
                    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
                }

                modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFator));
                shader.setMat4("model", modelMatrix);
                faces.at(x).draw();
                modelMatrix = glm::mat4(1.0f);
            }
    }
}