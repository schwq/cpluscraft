#include "model.h"
#include "libs/stb_image.h"

unsigned int TextureFromFile(std::string path);

void Model::draw(Shader& shader) {

	for (unsigned int x = 0; x < meshes.size(); x++) {
		meshes[x].draw(shader);
	}
}

void Model::loadModel(std::string path) {
	Assimp::Importer imp;
	const aiScene* scene = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		errorLog("Error: Assimp: ", imp.GetErrorString());
		return;
	}
	
	msgLog(path);
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int x = 0; x < node->mNumMeshes; x++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[x]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int x = 0; x < node->mNumChildren; x++) {
		processNode(node->mChildren[x], scene);
	}
 }

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureInfo> textures;

	for (unsigned int x = 0; x < mesh->mNumVertices; x++) {

		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[x].x;
		vector.y = mesh->mVertices[x].y;
		vector.z = mesh->mVertices[x].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[x].x;
		vector.y = mesh->mNormals[x].y;
		vector.z = mesh->mNormals[x].z;
		vertex.aNormal = vector;

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][x].x;
			vec.y = mesh->mTextureCoords[0][x].y;
			vertex.texCoords = vec;
		}
		else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (unsigned int x = 0; x < mesh->mNumFaces; x++) {
		aiFace face = mesh->mFaces[x];
		for (unsigned int y = 0; y < face.mNumIndices; y++) {
			indices.push_back(face.mIndices[y]);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<TextureInfo> diffuseMaps = loadMaterialTexture(mat, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<TextureInfo> specularMaps = loadMaterialTexture(mat, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<TextureInfo> Model::loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName) {
	std::vector<TextureInfo> textures;
	for (unsigned int x = 0; x < mat->GetTextureCount(type); x++) {
		aiString str;
		mat->GetTexture(type, x, &str);
		bool skip = false;
		for (unsigned int y = 0; y < texturesLoaded.size(); y++) {
			if (std::strcmp(texturesLoaded[y].path.data(), str.C_Str()) == 0) {
				textures.push_back(texturesLoaded[y]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			TextureInfo tex;
			tex.id = TextureFromFile(str.C_Str());
			tex.name = typeName;
			tex.path = str.C_Str();
			textures.push_back(tex);
			texturesLoaded.push_back(tex);
		}
	}
	return textures;
}

unsigned int TextureFromFile(std::string path) {

	std::string result = (currentOSPath("\\source\\models", "hel") + path);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(result.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		std::cout << "Texture success to load at path: " << path << std::endl;
		std::cout << "Texture success to load at result: " << result << std::endl;

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		std::cout << "Texture failed to load at result: " << result << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
