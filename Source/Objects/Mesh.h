#ifndef _MESH_H_
#define _MESH_H_

#include "../Common.h"
#include "../LogSystem.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 aNormal;
	glm::vec2 texCoords;
};

struct TextureInfo {
	std::string name;
	uint id;
	std::string path;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureInfo> textures);
    ~Mesh() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }
	void draw(Shader& shader);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureInfo> textures;

	uint VAO;

private:

	uint VBO, EBO;
	void setupMesh();
};

#endif