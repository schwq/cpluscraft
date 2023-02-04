#ifndef _MESH_H_
#define _MESH_H_

#include "../common.h"
#include "../error.h"
#include "shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 aNormal;
	glm::vec2 texCoords;
};

struct TextureInfo {
	std::string name;
	unsigned int id;
	std::string path;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureInfo> textures);
	void draw(Shader& shader);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureInfo> textures;

	unsigned int VAO;

private:

	unsigned int VBO, EBO;
	void setupMesh();
};

#endif