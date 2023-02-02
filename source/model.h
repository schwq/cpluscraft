#ifndef _MODEL_H_
#define _MODEL_H_

#include "error.h"
#include "common.h"
#include "mesh.h"

class Model {
public:
	Model(std::string path) { loadModel(path); }
	void draw(Shader& shader);
private:
	std::vector<Mesh> meshes;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureInfo> loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName);
	std::vector<TextureInfo> texturesLoaded;
};	

#endif