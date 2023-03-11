#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Libraries/stb_image.h"

uint Texture::textureCount = 0;

Texture::Texture(const char* texturePath,std::string name, uint format) : name(name) {
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 0);

	if (data) {

		if (channels == 1) {
			format = GL_RED;
		}
		else if (channels == 3) {
			format = GL_RGB;
		}
		else if (channels == 4) {
			format = GL_RGBA;
		}
	
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);



		logMessage("Success: Texture ", name, textureCount ," Compilated created with success! ID: ", getID());
		textureCount++;

	}
	else {
		logError("Error: Cannot create texture", name , textureCount,"! Path: " , texturePath);
	}
	stbi_image_free(data);
}

Texture::Texture(std::vector<std::string> paths, std::string name, uint format) : name(name) {
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	int width, height, channels;
	unsigned char* data = nullptr;
	for(uint x = 0; x < paths.size(); x++) {
		const char* temp_path = paths.at(x).c_str();
		data  = stbi_load(temp_path, &width, &height, &channels, 0);
		if(data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
           
			logMessage("Success: CubeMap ", name, textureCount, " loaded successfully! ID: ", getID());
			textureCount++;


		} else {
			logError("Error: Cannot load cubemap ", name, textureCount, " at path: ", paths[x]);
		}
	}
	if(data != nullptr) {
		stbi_image_free(data);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint  Texture::getID() {
	return textureID;
}

