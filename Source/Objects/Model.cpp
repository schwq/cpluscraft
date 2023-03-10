#include "Model.h"
#include "../Libraries/stb_image.h"

uint TextureFromFile(std::string path);

void Model::draw(Shader& shader) {

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

	for (uint x = 0; x < meshes.size(); x++) {
		meshes[x].draw(shader);
	}

	 this->model = glm::mat4(1.0f);

}

void Model::loadModel(std::string path) {
	Assimp::Importer imp;
	const aiScene* scene = imp.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		logError("Error: Assimp: ", imp.GetErrorString());
		return;
	}
	processNode(scene->mRootNode, scene);
}

void Model::translate(glm::vec3 positionVec) {
    position = positionVec;
}

void Model::scale(glm::vec3 scaleVec) {
    scaling = scaleVec;
}

void Model::rotate(RotationAxis axis, float fator) {
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

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (uint x = 0; x < node->mNumMeshes; x++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[x]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (uint x = 0; x < node->mNumChildren; x++) {
		processNode(node->mChildren[x], scene);
	}
 }

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureInfo> textures;

	for (uint x = 0; x < mesh->mNumVertices; x++) {

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

	for (uint x = 0; x < mesh->mNumFaces; x++) {
		aiFace face = mesh->mFaces[x];
		for (uint y = 0; y < face.mNumIndices; y++) {
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
	for (uint x = 0; x < mat->GetTextureCount(type); x++) {
		aiString str;
		mat->GetTexture(type, x, &str);
		bool skip = false;
		for (uint y = 0; y < texturesLoaded.size(); y++) {
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

uint TextureFromFile(std::string path) {

#ifdef defined(_WIN32) || defined(__CYGWIN__)  

	std::replace(path.begin(), path.end(), '/', '\\');

#endif
	stbi_set_flip_vertically_on_load(true);
	std::string result = (currentOSPath("\\source\\resources\\models", "/resources/models") + path);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	uint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

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

		logMessage("Success! Texture created with success! ID: ", textureID);
		stbi_image_free(data);
	}
	else
	{
		
		stbi_image_free(data);
	}
	glBindTexture(GL_TEXTURE_2D, NULL);
	return textureID;
}
