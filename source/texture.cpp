#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

Texture::Texture(const char* texturePath, unsigned int format) {

	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	defaultConfiguration();

	int width, height, channels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 0);

	if (data) {
		GLenum format = GL_RGB;
		if (channels == 1) {
			format = GL_RED;
		}
		else if (channels == 3) {
			format = GL_RGB;
		}
		else if (channels == 4) {
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_INT, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		errorLog("Error: Cannot create texture!", texturePath);
	}
	stbi_image_free(data);
}

void Texture::defaultConfiguration() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {}

unsigned int Texture::getID() {
	return textureID;
}
