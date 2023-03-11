#ifndef _MODEL_H_
#define _MODEL_H_

#include "../LogSystem.h"
#include "../Common.h"
#include "Mesh.h"
#include "Shapes.h"

class Model {
public:
	Model(std::string path) { loadModel(path); }
	void draw(Shader& shader);
	void translate(glm::vec3 positionVec);
    void scale(glm::vec3 scaleVec);
    void rotate(RotationAxis axis, float fator);
private:
	std::vector<Mesh> meshes;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureInfo> loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName);
	std::vector<TextureInfo> texturesLoaded;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 scaling = glm::vec3(1.0f);
    float Zrotation = 0.0f;
    float Xrotation = 0.0f;
    float Yrotation = 0.0f;
};	

#endif