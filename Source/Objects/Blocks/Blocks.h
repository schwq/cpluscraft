#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "../../LogSystem.h"
#include "../../Common.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../Shapes.h"

class Block;

enum FaceOrientation {
    Top = 0,
    Bottom = 1,
    Right = 2,
    Left = 3, 
    Front = 4,
    Back = 5
};

extern std::string FaceOrientationToString(FaceOrientation orientation);


struct Fragment {
    Fragment(glm::vec3 vc1, glm::vec3 vc2, glm::vec3 vc3, FaceOrientation orientation) : vc1(vc1), vc2(vc2), vc3(vc3), orientation(orientation) {};
    glm::vec3 vc1 = glm::vec3(1.0f);
    glm::vec3 vc2 = glm::vec3(1.0f);
    glm::vec3 vc3 = glm::vec3(1.0f);
    FaceOrientation orientation; 
};

class Face {
public:
    Face(Texture& texture, Shader& shader, Block& parentBlock, FaceOrientation orientation);
    void draw();
    void setTexture();
    uint getID() { return faceID; }
    void setShouldDraw(bool draw) { shouldDraw = draw; }
    bool getShouldDraw() { return shouldDraw; }
    FaceOrientation getOrientation() { return orientation; }
    Block& getParentBlock() { return parentBlock; }

private:
    Texture& texture;
    FaceOrientation orientation;
    Shader& shader;
    Block& parentBlock;
    uint faceID = 0;
    static uint ID;
    uint verticesNum;
    bool shouldDraw = true;
    uint VAO, VBO;

    const GLfloat topVertices[100] = {
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, // top
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f 
    };

    const GLfloat bottomVertices[100] = {
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, // bottom
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, 
    };

    const GLfloat backVertices[100] = {
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, // back
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 
    };

    const GLfloat frontVertices[100] = {
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, //  front
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 
    };

    const GLfloat rightVertices[100] = {
         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, // right
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 
    };

    const GLfloat leftVertices[100] = {
         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, // left
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    };

};

class Block {
public:

    Block(Texture& texture, Shader& shader, std::string name = LITERAL_NULL,glm::vec3 initialPos = glm::vec3(1.0f));
    //Block(std::vector<Texture&> textures, Shader& shader, std::string name = "null" ,glm::vec3 initialPos = glm::vec3(1.0f)) {};
    ~Block() {};

    void draw();
    Face& acessFaceOrientation(FaceOrientation orientation) {
        for(uint x = 0; x < 6; x++) {
            if(faces.at(x).getOrientation() == orientation) {
                return faces.at(x);
            }
        }
    };
    Face& acessFaceAt(uint x) { return faces.at(x); }

    void translate(glm::vec3 value);
    void rotate(RotationAxis axis, float value);
    void scale(float value);
    std::string getName() { return name; }
    uint getID() { return ID; }
    glm::mat4 getModelMatrix() { return modelMatrix; }
    glm::mat4 getModelMatrixPos() {
        return glm::translate(glm::mat4(1.0f), this->position);
    }
    std::vector<Fragment> fragments = {
        Fragment(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), Top),
        Fragment(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), Top),
        Fragment(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), Bottom),
        Fragment(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), Bottom),
        Fragment(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), Back),
        Fragment(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), Back),
        Fragment(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), Front),
        Fragment(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), Front),
        Fragment(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), Right),
        Fragment(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), Right),
        Fragment(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), Left),
        Fragment(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), Left)
    };

private:

    std::string name;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    std::vector<Face> faces;
    Texture& texture;
    Shader& shader;
    glm::vec3 position = glm::vec3(1.0f);
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;
    float scaleFator = 1.0f;

    uint ID;
    static uint countID;
};

#endif